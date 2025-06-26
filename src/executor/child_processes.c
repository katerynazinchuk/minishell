/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:31:59 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/26 17:23:31 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child_left(t_ast_node *node, t_session *session, int *pipe_fd);
static void	execute_child_right(t_ast_node *node, t_session *session, int *pipe_fd);

pid_t	child_left(t_ast_node *node, t_session *session, int *pipe_fd)
{
	pid_t	proc_id;

	proc_id = fork();
	if (proc_id < 0)
	{
		close_pipe_fd(pipe_fd);
		check_error(errno, "child process", GENERAL);
		return (-1);
	}
	else if (proc_id == 0)
		execute_child_left(node, session, pipe_fd);
	return (proc_id);
}

pid_t	child_right(t_ast_node *node, t_session *session, int *pipe_fd)
{
	pid_t	proc_id;

	proc_id = fork();
	if (proc_id < 0)
	{
		close_pipe_fd(pipe_fd);
		check_error(errno, "child process", GENERAL);
		return (-1);
	}
	else if (proc_id == 0)
		execute_child_right(node, session, pipe_fd);
	return (proc_id);
}

static void	execute_child_left(t_ast_node *node, t_session *session, int *pipe_fd)
{
	int	exit_status;

	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		close_pipe_fd(pipe_fd);
		free_in_fork(session, NULL);
		exit (check_error(errno, "dup2 to stdout failed", GENERAL));
	}
	close_pipe_fd(pipe_fd);
	exit_status = run_ast(node, session);
	free_in_fork(session, NULL);
	exit(exit_status);
}

static void	execute_child_right(t_ast_node *node, t_session *session, int *pipe_fd)
{
	int	exit_status;

	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		close_pipe_fd(pipe_fd);
		free_in_fork(session, NULL);
		exit (check_error(errno, "dup2 to stdin failed", GENERAL));
	}
	close_pipe_fd(pipe_fd);
	exit_status = run_cmd(node, session);
	free_in_fork(session, NULL);
	exit(exit_status);
}


/* 
pid_t	child_left(t_ast_node *node, t_session *session, int *pipe_fd)
{
	pid_t	proc_id;
	int		exit_status;

	proc_id = fork();
	if (proc_id < 0)
	{
		close_pipe_fd(pipe_fd);
		check_error(errno, "child process", GENERAL);
		return (-1);
	}
	else if (proc_id == 0)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			close_pipe_fd(pipe_fd);
			free_in_fork(session, NULL);
			exit (check_error(errno, "dup2 to stdout failed", GENERAL));
		}
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
		check_error(errno, "child process", GENERAL);
		return (-1);
	}
	else if (proc_id == 0)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			close_pipe_fd(pipe_fd);
			free_in_fork(session, NULL);
			exit (check_error(errno, "dup2 to stdin failed", GENERAL));
		}
		close_pipe_fd(pipe_fd);
		exit_status = run_cmd(node, session);
		free_in_fork(session, NULL);
		exit(exit_status);
	}
	return (proc_id);
} */