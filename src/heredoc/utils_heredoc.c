/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:40:54 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/24 13:46:16 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void heredoc_foreach_redir(t_redir *redir, t_session *ctx, void (*func)(t_redir *, t_session *))
{
	if (!redir)
		return;
	if (redir->type == RED_HEREDOC)
	{
		func(redir, ctx);
	}
	heredoc_foreach_redir(redir->next, ctx, func);
}

void heredoc_foreach_ast(t_ast_node *node, t_session *ctx ,void (*func)(t_redir *, t_session *))
{
	if (!node)
		return;
	if (node->type == AST_COMMAND && node->redir)
	{
		heredoc_foreach_redir(node->redir, ctx, func);
	}
	else {
		heredoc_foreach_ast(node->left, ctx, func);
		heredoc_foreach_ast(node->right, ctx, func);	
	}
}
