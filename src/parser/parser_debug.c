/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:49:57 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/01 11:41:47 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(char **args)
{
	int	i;

	if (args == NULL || *args == NULL)
		return ;
	i = 0;
	while (args[i])
	{
		printf("[%s] ", args[i]);
		i++;
	}
}

void	print_redirect(t_redir *head)
{
	char	*map[4];

	map[0] = "<";
	map[1] = ">";
	map[2] = ">>";
	map[3] = "<<";
	while (head != NULL)
	{
		printf("%s'%s' ", map[head->type], head->connection);
		head = head->next;
	}
}

void	print_node(t_ast_node *node, int depth)
{
	char		*map[2];
	t_ast_node	*left;
	t_ast_node	*right;
	int			i;

	map[0] = "AST_PIPE:    ";
	map[1] = "AST_COMMAND: ";
	if (!node)
		return ;
	left = node->left;
	right = node->right;
	i = 0;
	while (i < depth)
	{
		printf(" ");
		i++;
	}
	printf("%s", map[node->type]);
	print_args(node->value);
	print_redirect(node->redir);
	printf("\n");
	print_node(left, depth + 1);
	print_node(right, depth + 1);
}
