/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:40:57 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/09 15:52:25 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"
#include <fcntl.h>

void expand_heredoc(t_redir *redir, t_session *session)
{	
	int heredoc_id;
	char *heredoc_id_str;
	char *heredoc_file_name;
	int fd;
	char *line;
	char *tmp;

	heredoc_id = session->heredoc_count++;
	heredoc_id_str = ft_itoa(heredoc_id);
	if (!heredoc_id_str)
	{
		malloc_error(&session->shell->last_exit_status);
		return;
	}
	heredoc_file_name = ft_strjoin("/tmp/heredoc_", heredoc_id_str);
	free(heredoc_id_str);
	if (!heredoc_file_name)
	{
		malloc_error(&session->shell->last_exit_status);
		return;
	}
	fd = open("/tmp", O_TMPFILE | O_RDWR, 0600);
	// fd = open(heredoc_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell: open");
		free(heredoc_file_name);
		session->shell->last_exit_status = 1;
		return;
	}
	while (1)
	{
		tmp = NULL;
		line = readline("heredoc> ");
		if (!line)
		{
			free(heredoc_file_name);
			close(fd);
			session->shell->last_exit_status = 1;
			return;
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
			line = tmp;
			// write(fd, tmp, ft_strlen(tmp));
			// write(fd, "\n", 1);
			// free(line);
			// free(tmp);
			// continue;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		// if(tmp)
		// 	free(tmp);
		// else
		// {
		// 	write(fd, line, ft_strlen(line));
		// 	write(fd, "\n", 1);
		// 	free(line);
		// }
	}
	close(fd);
	if (redir->connection)
		free(redir->connection);
	redir->connection = heredoc_file_name;
	redir->type = RED_IN;//we need this cause it's the same processing as RED_IN
	// redir->type = RED_HEREDOC;
}

void heredoc(t_ast_node *node, t_session *session)
{
	heredoc_foreach_ast(node, session, expand_heredoc);
}

