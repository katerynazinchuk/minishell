/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:40:57 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/21 17:02:35 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"
#include <fcntl.h>

int event_handler(void)
{
	return 0;
}

char *create_heredoc_filename(int heredoc_id, int *exit_status)//TODO do we need exit status like this ?
{
	char *id_str;
	char *filename;

	id_str = ft_itoa(heredoc_id);
	if (!id_str)
	{
		*exit_status = check_error(ENOMEM, "minishell : heredoc");
		return (NULL);
	}
	filename = ft_strjoin("/tmp/heredoc_", id_str);//TODO valgrind
	free(id_str);
	if(!filename)
	{
		*exit_status = check_error(ENOMEM, "minishell : heredoc");
		return (NULL);
	}
	return(filename);
}

int write_heredoc_lines(t_redir *redir, t_session *session, int fd)
{
	char *line;
	char *tmp;
	setsignal(HEREDOC_SIG);
	rl_event_hook = event_handler;
	while (1)
	{
		tmp = NULL;
		line = readline("heredoc> ");
		if (!line)
			break;
		if (g_signal != 0)
		{
			session->shell->status = 128 + g_signal;
			setsignal(MAIN_SIG);
			free(line);
			return (1);
		}
		if (ft_strcmp(line, redir->connection) == 0)
		{
			free(line);
			break;
		}
		if(redir->quoted != QUOTED)
		{
			tmp = expand_value(line, session->shell);
			free(line);
			if(!tmp)
				return (2);
			line = tmp;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	setsignal(MAIN_SIG);
	return (0);
}

void expand_heredoc(t_redir *redir, t_session *session)
{	
	int heredoc_id;
	char *heredoc_filename;
	int fd;
	int status;

	heredoc_id = session->heredoc_count++;
	heredoc_filename = create_heredoc_filename(heredoc_id, &session->shell->status);
	if(!heredoc_filename)
		return ;
	fd = open(heredoc_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell: open");
		free(heredoc_filename);
		session->shell->status = 1;
		return;
	}
	status = write_heredoc_lines(redir, session, fd);
	if(status == 2)
	{
		malloc_error(&session->shell->status);
		close(fd);
		free(heredoc_filename);
		return ;
	}
	close(fd);
	if (status == 1)
	{
		free(heredoc_filename);
		return ;
	}
	if (redir->connection)
		free(redir->connection);
	redir->connection = heredoc_filename;
}

void heredoc(t_ast_node *node, t_session *session)
{
	heredoc_foreach_ast(node, session, expand_heredoc);
}