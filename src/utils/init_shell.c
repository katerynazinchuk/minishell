/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:27:31 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/25 16:30:48 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	shell->env_list = fill_env_list(env);//TODO how we handle case if !shell->env_list ?
	// shell->tokens = NULL;
	// shell->ast = NULL;
	// shell->line = NULL;
	shell->last_exit_status = 0;
	// shell->prompt = "minishell> ";
}

void	cleanup_cycle(t_session *session)
{
	if (session->tokens)
	{
		free_token_list(session->tokens);
		session->tokens = NULL;
	}
	if (session->ast)
	{
		free_ast(session->ast);
		session->ast = NULL;
	}
	if (session->line)
	{
		free(session->line);
		session->line = NULL;
	}
}
// TODO if uncomment previous if statement we have code dump.
//Why? -> cause pointer after previuos free didnt set up for NULL


/* typedef struct s_shell
{
	t_env_list		*env_list;
	int				last_exit_status;
}	t_shell;

typedef struct s_session
{
	t_shell			*shell;
	t_token_list	*tokens;
	t_ast_node		*ast;
	char			*line;
	char			*prompt;
}	t_session
 */

void	init_session(t_session *session, t_shell *shell)
{
	session->shell = shell;
	session->tokens = NULL;
	session->ast = NULL;
	session->line = NULL;
	session->prompt = "minishell> ";
}