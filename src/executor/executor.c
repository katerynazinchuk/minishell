/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:08:39 by tchernia          #+#    #+#             */
/*   Updated: 2025/07/03 18:14:24 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_fork_fail(t_session *session, int *pipe_fd, pid_t id_left);
static int	handle_fork_fail(t_session *session, int *pipe_fd, pid_t id_left);

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
		session->shell->status = builtin_fn(node->value, \
session->shell->env_list);
	else
		session->shell->status = run_external(node, session);
	if (session->shell->status == 131)
		ft_putendl_fd("Quit (core dumped)", 1);
	else if (session->shell->status == 130)
		ft_putendl_fd("", 1);
	else if (session->shell->status == 143)
		ft_putendl_fd("terminated", 1);
	return (session->shell->status);
}

int	run_pipe(t_ast_node *ast, t_session *session)
{
	pid_t	id_left;
	pid_t	id_right;
	int		status;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		return (check_error(errno, "pipe", GENERAL));
	id_left = child_left(ast->left, session, pipe_fd);
	if (id_left < 0)
		return (handle_fork_fail(session, pipe_fd, id_left));
	id_right = child_right(ast->right, session, pipe_fd);
	if (id_right < 0)
		return (handle_fork_fail(session, pipe_fd, id_left));
	close_pipe_fd(pipe_fd);
	waitpid(id_left, NULL, 0);
	waitpid(id_right, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static int	handle_fork_fail(t_session *session, int *pipe_fd, pid_t id_left)
{
	free_in_fork(session, NULL);
	close_pipe_fd(pipe_fd);
	if (id_left > 0)
		waitpid(id_left, NULL, 0);
	return (1);
}
