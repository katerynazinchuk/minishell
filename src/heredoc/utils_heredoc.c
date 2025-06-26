/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:40:54 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/26 16:51:34 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	heredoc_redir(t_redir *redir, t_session *ctx, \
// 									void (*func)(t_redir *, t_session *))
// {
// 	if (!redir)
// 		return ;
// 	if (redir->type == RED_HEREDOC)
// 	{
// 		func(redir, ctx);
// 	}
// 	heredoc_redir(redir->next, ctx, func);
// }

static void	heredoc_redir(t_redir *redir, t_session *ctx)//, \
									//void (*func)(t_redir *, t_session *))
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
	// heredoc_redir(redir->next, ctx, func);
}

void	heredoc_ast(t_ast_node *node, \
						t_session *ctx)//, void (*func)(t_redir *, t_session *))
{
	if (!node)
		return ;
	if (node->type == AST_COMMAND && node->redir)
	{
		heredoc_redir(node->redir, ctx);//, func);
	}
	else
	{
		heredoc_ast(node->left, ctx);//, func);
		heredoc_ast(node->right, ctx);//, func);
	}
}
