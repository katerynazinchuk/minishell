/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:31:44 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/01 11:50:50 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_ast_node(t_ast_type type, char **command)
{
	t_ast_node	*ast_node;

	ast_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!ast_node)
	{
		check_error(ENOMEM, "ast_node", GENERAL);
		return (NULL);
	}
	ast_node->type = type;
	ast_node->value = command;
	ast_node->redir = NULL;
	ast_node->left = NULL;
	ast_node->right = NULL;
	return (ast_node);
}

t_red_type	define_redirection(t_tok_type token_type)
{
	if (token_type == T_IN)
		return (RED_IN);
	if (token_type == T_OUT)
		return (RED_OUT);
	if (token_type == T_APPEND)
		return (RED_APPEND);
	if (token_type == T_HEREDOC)
		return (RED_HEREDOC);
	return (-1);
}
