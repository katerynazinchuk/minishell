/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:40:54 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/26 19:01:16 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_heredoc_filename(int heredoc_id, int *exit_status)
{
	char	*id_str;
	char	*filename;

	id_str = ft_itoa(heredoc_id);
	if (!id_str)
	{
		*exit_status = check_error(ENOMEM, "heredoc", GENERAL);
		return (NULL);
	}
	filename = ft_strjoin("/tmp/heredoc_", id_str);
	free(id_str);
	if (!filename)
	{
		*exit_status = check_error(ENOMEM, "heredoc", GENERAL);
		return (NULL);
	}
	return (filename);
}

void	expand_heredoc(t_redir *redir, t_session *session)
{
	int		heredoc_id;
	char	*heredoc_name;
	int		fd;

	heredoc_id = session->heredoc_count++;
	heredoc_name = create_heredoc_filename(heredoc_id, &session->shell->status);
	if (!heredoc_name)
		return ;
	fd = open(heredoc_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(heredoc_name);
		session->shell->status = check_error(errno, "heredoc", GENERAL);
		return ;
	}
	if (write_heredoc_lines(redir, session, fd))
	{
		close(fd);
		free(heredoc_name);
		return ;
	}
	close(fd);
	if (redir->connection)
		free(redir->connection);
	redir->connection = heredoc_name;
}

static void	heredoc_redir(t_redir *redir, t_session *ctx)
{
	t_redir	*current;

	current = redir;
	if (!current)
		return ;
	while (current)
	{
		if (current->type == RED_HEREDOC)
		{
			expand_heredoc(current, ctx);
		}
		if (ctx->shell->status > 128)
			return ;
		current = current->next;
	}
}

void	heredoc_ast(t_ast_node *node, t_session *ctx)
{
	if (!node)
		return ;
	if (node->type == AST_COMMAND && node->redir)
	{
		heredoc_redir(node->redir, ctx);
	}
	else
	{
		heredoc_ast(node->left, ctx);
		if (ctx->shell->status > 128)
			return ;
		heredoc_ast(node->right, ctx);
	}
}

void	heredoc(t_ast_node *node, t_session *session)
{
	heredoc_ast(node, session);
}
