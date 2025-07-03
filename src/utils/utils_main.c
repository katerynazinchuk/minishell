/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:25:07 by tchernia          #+#    #+#             */
/*   Updated: 2025/07/03 18:15:08 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ignore_args(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

int	shell_exit(t_session *session)
{
	write(1, "exit\n", 5);
	free_for_fork(session);
	return (1);
}

void	destroy_shell(t_shell *shell)
{
	free_env_list(shell->env_list);
	shell->env_list = NULL;
	destroy_fd(shell->fd);
}

void	destroy_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}
