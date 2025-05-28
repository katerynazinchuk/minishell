/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Amirre <Amirre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:07:56 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/28 13:58:44 by Amirre           ###   ########.fr       */
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

void	init_cmd_info(t_cmd_info *cmd_info, t_execute *exe)
{
	cmd_info->argv;            // command + arguments
	cmd_info->infile;           // for `<`
	cmd_info->outfile;          // for `>` or `>>`
	cmd_info->append_mode;        // 1 if >>, 0 if >
	cmd_info->is_heredoc;         // 1 if heredoc, 0 otherwise
	cmd_info->*heredoc_delim;    // heredoc delimiter
	//struct s_command	*next; // next in pipe chain
}

