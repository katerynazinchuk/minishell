/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_external.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:59:32 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/05 15:40:26 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	run_external(t_ast_node *node, t_shell *shell)
{
	pid_t	proc_id;
	int		exit_status;
	char	**env_arr;

	proc_id = fork();
	if (proc_id < 0)
		return (1);//TODO check return
	if (proc_id == 0)
	{
		env_arr = env_to_arr(shell->env_list); //can be NULL
		if (!env_arr)
		{
			free_env_list(shell->env_list);
			//free_ast
			exit (1);
		}
		if(execve(node->value[0], node->value, env_arr) == -1)
		{
			free_arr(env_arr);
			free_env_list(shell->env_list);
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
