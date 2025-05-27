/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:07:56 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/27 17:54:18 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_execute(t_execute *exe, t_session *session)
{
	exe->shell = session->shell;
	exe->ast = session->ast;
	exe->fd[0] = -1;
	exe->fd[1] = -1;
	// int			prev_fd;
	// t_list		*pid_list;
	// t_list		*heredoc_fds;
}

void	init_cmd_info()
{
	
}
