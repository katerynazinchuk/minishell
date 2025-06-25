/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:08:39 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/25 17:18:56 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_session *session)
{
	session->shell->status = run_ast(session->ast, session);
	restore_fd(session);
}

int	run_ast(t_ast_node *ast, t_session *session)
{
	if (!ast)
		return (0);
	if (ast->type == AST_PIPE)
		return (run_pipe(ast, session));
	else
		return (run_cmd(ast, session));
}

int	run_cmd(t_ast_node *node, t_session *session)
{
	t_builtin_fn	builtin_fn;

	if (apply_redir(node->redir))
		return (1);
	if (!node->value[0])
		return (0);
	builtin_fn = get_builtin_fn(node->value[0]);
	if (builtin_fn)
		session->shell->status = builtin_fn(node->value, session->shell->env_list);
	else
		session->shell->status = run_external(node, session);
	return (session->shell->status);
}

int	run_pipe(t_ast_node *ast, t_session *session)
{
	pid_t	id_left;
	pid_t	id_right;
	int		status;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		write(2, "Pipe error \n", 13);
	id_left = child_left(ast->left, session, pipe_fd);
	if (id_left < 0)
	{
		free_in_fork(session, NULL);
		return (1);
	}
	id_right = child_right(ast->right, session, pipe_fd);
	if (id_right < 0)
	{
		free_in_fork(session, NULL);
		waitpid(id_left, NULL, 0);
	}
	close_pipe_fd(pipe_fd);
	waitpid(id_left, NULL, 0);
	waitpid(id_right, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

pid_t	child_left(t_ast_node *node, t_session *session, int *pipe_fd)
{
	pid_t	proc_id;
	int		exit_status;

	proc_id = fork();
	if (proc_id < 0)
	{
		close_pipe_fd(pipe_fd);
		return (-1);
	}
	else if (proc_id == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close_pipe_fd(pipe_fd);
		exit_status = run_ast(node, session);
		free_in_fork(session, NULL);
		exit(exit_status);
	}
	return (proc_id);
}

pid_t	child_right(t_ast_node *node, t_session *session, int *pipe_fd)
{
	pid_t	proc_id;
	int		exit_status;

	proc_id = fork();
	if (proc_id < 0)
	{
		close_pipe_fd(pipe_fd);
		return (-1);
	}
	else if (proc_id == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close_pipe_fd(pipe_fd);
		exit_status = run_cmd(node, session);
		free_in_fork(session, NULL);
		exit(exit_status);
	}
	return (proc_id);
}
