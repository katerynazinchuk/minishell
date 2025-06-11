/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:40:57 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/11 19:17:06 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"
#include <fcntl.h>

char *create_heredoc_filename(int heredoc_id, int *exit_status)
{
	char *id_str;
	char *filename;

	id_str = ft_itoa(heredoc_id);
	if (!id_str)
	{
		malloc_error(exit_status);
		return (NULL);
	}
	filename = ft_strjoin("/tmp/heredoc_", id_str);
	free(id_str);
	if(!filename)
	{
		malloc_error(exit_status);
		return (NULL);
	}
	return(filename);
}

int write_heredoc_lines(t_redir *redir, t_session *session, int fd)
{
	char *line;
	char *tmp;
	//setsignal(heredoc)
	while (1)
	{
		tmp = NULL;
		line = readline("heredoc> ");
		if (!line)
			return (0);
		if (ft_strcmp(line, redir->connection) == 0)
		{
			free(line);
			break;
		}
		if(redir->quoted != QUOTED)
		{
			tmp = expand_value(line, session->shell);
			free(line);
			line = tmp;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (1);
}

void expand_heredoc(t_redir *redir, t_session *session)
{	
	int heredoc_id;
	char *heredoc_filename;
	int fd;

	heredoc_id = session->heredoc_count++;
	heredoc_filename = create_heredoc_filename(heredoc_id, &session->shell->last_exit_status);
	if(!heredoc_filename)
		return ;
	fd = open(heredoc_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell: open");
		free(heredoc_filename);
		session->shell->last_exit_status = 1;
		return;
	}
	if(!write_heredoc_lines(redir, session, fd))
	{
		malloc_error(&session->shell->last_exit_status);
		return ;
	}
	close(fd);
	if (redir->connection)
		free(redir->connection);
	redir->connection = heredoc_filename;
}

void heredoc(t_ast_node *node, t_session *session)
{
	heredoc_foreach_ast(node, session, expand_heredoc);
}