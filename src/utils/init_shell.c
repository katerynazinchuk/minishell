/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:27:31 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/26 19:27:26 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	shell->env_list = fill_env_list(env);// TODO: how we handle case if !shell->env_list ?
	shell->fd[STDIN_FILENO] = dup(STDIN_FILENO);
	shell->fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
	shell->status = 0;
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
	char		*tmp_name;
	char		*new_prompt;
	const char	*color = "\001\033[1;35m\002";

	tmp_name = ft_strdup(getenv("LOGNAME"));
	if (!tmp_name)
		tmp_name = ft_strdup("unknown");
	if (!tmp_name)
		return (check_error(ENOMEM, "prompt", GENERAL));
	new_prompt = ft_strjoin(color, tmp_name);
	free(tmp_name);
	tmp_name = NULL;
	if (!new_prompt)
		return (check_error(ENOMEM, "prompt", GENERAL));//TODO set malloc_error
	tmp_name = ft_strjoin(new_prompt, ":~$ \001\033[0m\002");
	free(new_prompt);
	if (!tmp_name)
		return (check_error(ENOMEM, "prompt", GENERAL));//TODO set malloc_error
	free(*prompt);
	*prompt = tmp_name;
	return (0);
}
