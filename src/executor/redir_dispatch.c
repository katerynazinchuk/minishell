/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_dispatch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:32:54 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/16 12:36:09 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* dup2(fd_what_I_already_have, fd_what_I_want_to_make) */
static bool	apply_in(t_redir *redir);
static bool	apply_out(t_redir *redir);
static bool	apply_append(t_redir *redir);
static bool	apply_heredoc(t_redir *redir);

/* hash map, acces via key*/
bool	apply_redir(t_redir *redir_list)
{
	static t_redir_handler handlers[] = {
		[RED_IN] = apply_in,
		[RED_OUT] = apply_out,
		[RED_APPEND] = apply_append,
		[RED_HEREDOC] = apply_heredoc
	};
	t_redir_handler	f;
	
	if (!redir_list)
		return (true);
	while (redir_list)
	{
		f = handlers[redir_list->type];
		if (!f || !f(redir_list))
			return (false);
		redir_list = redir_list->next;
	}
	return (true);
	}

/* we need to manage correct errors for open */
static bool	apply_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->connection, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error open file\n", 17);
		return (false);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		write(2, "Error dup2\n", 12);
		return (false);
	}
	close(fd);
	return (true);
}

static bool	apply_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->connection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		write(2, "Error open file\n", 17);
		return (false);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		write(2, "Error dup2\n", 12);
		return (false);
	}
	close(fd);
	return (true);
}

static bool	apply_append(t_redir *redir)
{
	int	fd;
	
	fd = open(redir->connection, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		write(2, "Error open file\n", 17);
		return (false);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		write(2, "Error dup2\n", 12);
		return (false);
	}
	close(fd);
	return(true);
}

static bool	apply_heredoc(t_redir *redir)
{
	int	fd;

	fd = open(redir->connection, O_RDONLY);
	if (fd < 0)
		{
		write(2, "Error open file\n", 17);
		return (false);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		write(2, "Error dup2\n", 12);
		return (false);
	}
	close(fd);
	unlink(redir->connection);
	return (true);
}

/* bool apply_red(t_redir *head)
{
	static t_redir_handler redmap[] = {
		applay_in,
		applay_out,
		applay_append,
		NULL
	};

	while (head)
	{
		if (redmap[red->type](head) == false)
			return (false);
		head = head->next;
	}
	return (true);
} */

	/* 		if (redir_list->type != RED_HEREDOC && redir_list > 0)//check with Katia when *redir_list can return -1
			{
				f = handlers[redir_list->type];
				if (!f || !f(redir_list))
					return (false);
			} */
