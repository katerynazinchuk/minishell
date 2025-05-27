/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:08:39 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/27 17:59:38 by tchernia         ###   ########.fr       */
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
	t_execute	exe;

	init_execute(&exe, session);
	//run_heredoc
	run_ast(exe.ast_node, &exe);
	// Відновили стандартні дескриптори
    // dup2(saved_stdin,  STDIN_FILENO);
    // dup2(saved_stdout, STDOUT_FILENO);
    // close(saved_stdin);
    // close(saved_stdout);
}

void	run_ast(t_ast_node *ast, t_execute *exe)
{
	if (!ast)
		return ;
	if (ast->type == AST_PIPE)
	{
		run_ast(ast->left, exe);
		run_ast(ast->right, exe);
	}
	else
	{
		run_cmd(ast, exe);
	}
}

void	run_cmd(t_ast_node *node, t_execute *exe)
{
	t_cmd_info	cmd_info;
	//redirect_validation
	//init_cmd_info
	if (builtin(cmd_info, exe))
		run_builtin(cmd_info, exe);
	else
		run_external(cmd_info, exe);
}



