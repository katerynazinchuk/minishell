/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:34:55 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/26 13:35:26 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	restore_fd(t_session *session)
{
	dup2(session->shell->fd[STDIN_FILENO], STDIN_FILENO);
	dup2(session->shell->fd[STDOUT_FILENO], STDOUT_FILENO);
}

void	close_pipe_fd(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int	free_in_fork(t_session *session, char **env_arr)
{
	if (env_arr)
		free_arr(env_arr);
	free_env_list(session->shell->env_list);
	free_ast(&session->ast);
	destroy_shell(session->shell);
	return (1);
}
