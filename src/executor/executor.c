/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:08:39 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/25 16:40:13 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* typedef struct	s_ast_node
{
	t_ast_type			type; 
	char				**value;//command
	t_redir				*redir;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node; */

void	executor(t_session *session)
{
	run_ast(session->ast, session->shell);
	// Відновили стандартні дескриптори
    // dup2(saved_stdin,  STDIN_FILENO);
    // dup2(saved_stdout, STDOUT_FILENO);
    // close(saved_stdin);
    // close(saved_stdout);
}

void	run_ast(t_ast_node *node, t_shell *shell)
{
	t_ast_node	*current;

	while(current)
	{
		if (current->type == AST_PIPE)
		{
			run_ast(current, shell);
		}
	}
}