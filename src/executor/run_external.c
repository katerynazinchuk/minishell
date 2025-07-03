/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_external.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:59:32 by tchernia          #+#    #+#             */
/*   Updated: 2025/07/03 13:15:21 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_cmd_in_child(t_ast_node *node, t_session *session, int status);

int	run_external(t_ast_node *node, t_session *session)
{
	pid_t	proc_id;
	int		exit_status;

	exit_status = 0;
	proc_id = fork();
	if (proc_id < 0)
		return (-1);
	if (proc_id == 0)
		run_cmd_in_child(node, session, exit_status);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(proc_id, &exit_status, 0);
	setsignal(MAIN_SIG);
	if (WIFSIGNALED(exit_status))
		return (128 + WTERMSIG(exit_status));
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (1);
}

static void	run_cmd_in_child(t_ast_node *node, t_session *session, int status)
{
	char	**env_arr;

	env_arr = env_to_arr(session->shell->env_list);
	if (!env_arr)
		exit (free_in_fork(session, NULL));
	status = find_path(node->value, session->shell->env_list);
	if (status > 1 || errno == ENOMEM)
	{
		free_in_fork(session, env_arr);
		exit (status);
	}
	setsignal(DEFAULT_SIG);
	if (execve(node->value[0], node->value, env_arr) == -1)
	{
		if (errno == ENOENT || errno == EACCES)
			status = check_error(CMD_NOT_FOUND, node->value[0], EXEC);
		free_in_fork(session, env_arr);
		exit (status);
	}
	exit(1);
}
