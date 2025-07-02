/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_dispatch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:32:54 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/25 17:20:15 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* dup2(fd_what_I_already_have, fd_what_I_want_to_make) */
static int	apply_in(t_redir *redir);
static int	apply_out(t_redir *redir);
static int	apply_append(t_redir *redir);
static int	apply_heredoc(t_redir *redir);

/* hash map, acces via key*/
int	apply_redir(t_redir *redir_list)
{
	static t_redir_handler	handlers[] = {
	[RED_IN] = apply_in,
	[RED_OUT] = apply_out,
	[RED_APPEND] = apply_append,
	[RED_HEREDOC] = apply_heredoc
	};
	t_redir_handler			f;

	if (!redir_list)
		return (0);
	while (redir_list)
	{
		f = handlers[redir_list->type];
		if (!f || f(redir_list))
			return (1);
		redir_list = redir_list->next;
	}
	return (0);
}

static int	apply_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->connection, O_RDONLY);
	if (fd < 0)
		return (check_error(errno, redir->connection, GENERAL));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (check_error(errno, redir->connection, GENERAL));
	close(fd);
	return (0);
}

static int	apply_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->connection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (check_error(errno, redir->connection, GENERAL));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (check_error(errno, redir->connection, GENERAL));
	close(fd);
	return (0);
}

static int	apply_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->connection, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (check_error(errno, redir->connection, GENERAL));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (check_error(errno, redir->connection, GENERAL));
	close(fd);
	return (0);
}

static int	apply_heredoc(t_redir *redir)
{
	int	fd;

	fd = open(redir->connection, O_RDONLY);
	if (fd < 0)
		return (check_error(errno, redir->connection, GENERAL));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (check_error(errno, redir->connection, GENERAL));
	close(fd);
	unlink(redir->connection);
	return (0);
}
