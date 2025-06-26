/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:40:57 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/26 19:01:11 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"
#include <fcntl.h>

int	event_handler(void)
{
	return (0);
}

int	handle_heredoc_sig(t_session *session, char *line)
{
	if (g_signal != 0)
	{
		session->shell->status = 128 + g_signal;
		setsignal(MAIN_SIG);
		free(line);
		return (1);
	}
	return (0);
}

int	is_delimeter(char *line, char *delimeter)
{
	if (ft_strcmp(line, delimeter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

char	*process_expansion(char *line, t_session *session)
{
	char	*expanded;

	expanded = expand_value(line, session->shell);
	free(line);
	if (!expanded)
	{
		session->shell->status = check_error(ENOMEM, "heredoc", GENERAL);
		return (NULL);
	}
	return (expanded);
}

int	write_heredoc_lines(t_redir *redir, t_session *session, int fd)
{
	char	*line;

	setsignal(HEREDOC_SIG);
	rl_event_hook = event_handler;
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (handle_heredoc_sig(session, line))
			return (1);
		if (is_delimeter(line, redir->connection))
			break ;
		if (redir->quoted != QUOTED)
		{
			line = process_expansion(line, session);
			if (!line)
				return (1);
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	setsignal(MAIN_SIG);
	return (0);
}

// int	write_heredoc_lines(t_redir *redir, t_session *session, int fd)
// {
// 	char	*line;
// 	char	*tmp;

// 	setsignal(HEREDOC_SIG);
// 	rl_event_hook = event_handler;
// 	while (1)
// 	{
// 		tmp = NULL;
// 		line = readline("heredoc> ");
// 		if (!line)
// 			break ;
// 		if (g_signal != 0)
// 		{
// 			session->shell->status = 128 + g_signal;
// 			setsignal(MAIN_SIG);
// 			free(line);
// 			return (1);
// 		}
// 		if (ft_strcmp(line, redir->connection) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (redir->quoted != QUOTED)
// 		{
// 			tmp = expand_value(line, session->shell);
// 			free(line);
// 			if (!tmp)
// 				return (2);
// 			line = tmp;
// 		}
// 		write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 	}
// 	setsignal(MAIN_SIG);
// 	return (0);
// }