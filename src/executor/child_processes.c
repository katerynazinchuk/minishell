/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:31:59 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/26 13:35:21 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
