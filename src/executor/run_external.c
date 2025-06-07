/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_external.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:59:32 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/05 18:57:30 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_external(t_ast_node *node, t_shell *shell)
{
	pid_t	proc_id;
	int		exit_status;
	char	**env_arr;
	// char	*full_path;
	
	write(1, "1\n", 2);
	write(1, node->value[0], ft_strlen(node->value[0]));
	exit_status = 0;
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

//execve will return ENOENT and we need to change it to " : command not found"