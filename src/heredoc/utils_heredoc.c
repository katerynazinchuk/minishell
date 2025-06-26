/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:40:54 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/26 17:10:14 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
