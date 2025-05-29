/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_dispatch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:32:54 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/29 15:37:33 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static bool	validate_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->connection, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}

static bool	validate_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->connection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (false);//TODO do we need to close fd in this case?
	close(fd);
	return (true);
}

static bool	validate_append(t_redir	*redir)
{
	int	fd;

	fd = open(redir->connection, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (false);
	close(fd);
	return(true);
	
}
//typedef enum	e_red_type
//{
//	RED_IN,//<
//	RED_OUT,//>
//	RED_APPEND,//>>
//	RED_HEREDOC,//<<
//}	t_red_type;

bool	validate_redir(t_redir *redir_list)
{
	static t_redir_handler handlers[] = {
		[RED_IN] = validate_in,
		[RED_OUT] = validate_out,
		[RED_APPEND] = validate_append,
		[RED_HEREDOC] = NULL
	};
	t_redir_handler f;
	if (!redir_list)
		return (false);
	while (redir_list)
	{
		if (redir_list->type != RED_HEREDOC && redir_list > 0)//check with Katia when *redir_list can return -1
		{
			f = handlers[redir_list->type];
			if (!f || !f(redir_list))
				return (false);
		}
		redir_list = redir_list->next;
	}
	return (true);
}
