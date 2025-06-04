/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_external.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:59:32 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/04 16:15:09 by tchernia         ###   ########.fr       */
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
		if(execve(node->value[0], node->value, env_arr))
		{
			exit_status = ;
			free_arr(env_arr);
			//do we need to free shell->env_list cause it is allocated ?
			exit (exit_status);
		}
	}
	return(proc_id);
}
