/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:05:29 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/01 11:49:40 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*find_last_pipe(t_token *head, t_token *end);

t_ast_node	*parse_command(t_token *head, t_token *end)
{
	t_token				*current;
	t_ast_node			*new_ast_node;
	t_command_parsing	*structure;

	current = head;
	new_ast_node = create_ast_node(AST_COMMAND, NULL);
	if (!new_ast_node)
		return (NULL);
	structure = extract_red_and_args(head, end);
	if (!structure)
	{
		free_ast(&new_ast_node);
		return (NULL);
	}
	new_ast_node->value = tokens_to_argv(structure->args);
	if (!new_ast_node->value)
		return (NULL);
	new_ast_node->redir = structure->redirect;
	free_structure(structure);
	return (new_ast_node);
}

t_ast_node	*parse_pipe(t_token *head, t_token *end)
{
	t_token		*last_pipe;
	t_ast_node	*new_ast_node;

	last_pipe = find_last_pipe(head, end);
	if (last_pipe)
	{
		new_ast_node = create_ast_node(AST_PIPE, NULL);
		if (!new_ast_node)
			return (NULL);
		new_ast_node->left = parse_pipe(head, last_pipe);
		if (!new_ast_node->left)
		{
			free_ast(&new_ast_node);
			return (NULL);
		}
		new_ast_node->right = parse_command(last_pipe->next, end);
		if (!new_ast_node->right)
		{
			free_ast(&new_ast_node);
			return (NULL);
		}
		return (new_ast_node);
	}
	return (parse_command(head, end));
}

static t_token	*find_last_pipe(t_token *head, t_token *end)
{
	t_token		*current;
	t_token		*last_pipe;

	current = head;
	last_pipe = NULL;
	while (current && current != end)
	{
		if (current->type == T_PIPE)
			last_pipe = current;
		current = current->next;
	}
	return (last_pipe);
}
