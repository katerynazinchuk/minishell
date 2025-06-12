/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:41:13 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/11 19:35:20 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cleanup_heredoc(t_redir *redir, t_session *session)
{
	(void)session;
	if (redir && redir->type == RED_HEREDOC)
	{
		if (redir->connection)
		{
			unlink(redir->connection);
			free(redir->connection);
			redir->connection = NULL;
		}
	}
	if (redir && redir->next)
		cleanup_heredoc(redir->next, session);
	if (redir && redir->next == NULL)
	{
		free(redir);
		redir = NULL;
	}
}