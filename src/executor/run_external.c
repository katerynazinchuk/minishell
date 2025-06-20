/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_external.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:59:32 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/16 12:46:45 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_external(t_ast_node *node, t_session *session)
{
	pid_t	proc_id;
	int		exit_status;
	char	**env_arr;

	exit_status = 0;
	proc_id = fork();
	if (proc_id < 0)
		return (-1);//TODO check return for fork_error
	if (proc_id == 0)
	{
		env_arr = env_to_arr(session->shell->env_list);
		if (!env_arr)
		{
			free_in_fork(session, NULL);
			errno = ENOMEM;
			perror("minishell executor ");
			exit (1);
		}
		if (!find_path(node->value, session->shell->env_list))
		{
			free_in_fork(session, env_arr);
			exit(check_error(ENOMEM, NULL));
			// errno = ENOMEM;
			// perror("minishell executor ");
			// exit(1);
		}
		if(execve(node->value[0], node->value, env_arr) == -1)
		{
			if (errno == ENOENT)
				exit_status = check_error(CMD_NOT_FOUND, node->value[0]);
			else
				exit_status = check_error(errno, "execve error");
				// perror("minishel execute ");
			free_in_fork(session, env_arr);
			exit (exit_status);
		}
		exit(1);
	}
	waitpid(proc_id, &exit_status, 0);
	if (WIFSIGNALED(exit_status))
		return(128 + WTERMSIG(exit_status));
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return(1);
}

//execve will return ENOENT and we need to change it to " : command not found"

