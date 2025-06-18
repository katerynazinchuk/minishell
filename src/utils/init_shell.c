/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Amirre <Amirre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:27:31 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/18 22:14:56 by Amirre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	shell->env_list = fill_env_list(env);//TODO how we handle case if !shell->env_list ?
	shell->fd[STDIN_FILENO] = dup(STDIN_FILENO);
	shell->fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
	shell->last_exit_status = 0;
}

void	free_for_fork(t_session *session)
{
	if (session->prompt)
	{
		free(session->prompt);
		session->prompt = NULL;
	}
	if (session->tokens)
	{
		free_token_list(session->tokens);
		session->tokens = NULL;
	}
	if (session->line)
	{
		free(session->line);
		session->line = NULL;
	}
	session->heredoc_count = 0;
}

void	init_session(t_session *session, t_shell *shell)
{
	session->shell = shell;
	session->tokens = NULL;
	session->ast = NULL;
	session->line = NULL;
	session->prompt = NULL;
	session->heredoc_count = 0;
}

int	update_prompt(char **prompt)
{
	char	*log_name;
	char	*new_prompt;

	log_name = ft_strdup(getenv("LOGNAME"));
	if (!log_name)
		log_name = ft_strdup("unknown");
	if (!log_name)
		return (check_error(ENOMEM));//TODO set malloc_error
	new_prompt = ft_strjoin(log_name, ":~$ ");
	free(log_name);
	if (!new_prompt)
		return ;//TODO set malloc_error
	free(*prompt);
	*prompt = new_prompt;
}

void	ignore_args(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}
