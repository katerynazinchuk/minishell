/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:00:29 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/30 17:01:51 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_redirects(t_redir *redir)
{
	t_redir *current;
	t_redir *next;

	current = redir;
	while (current)
	{
		next = current->next;
		free(current->connection); // assumes connection is dynamically allocated
		free(current);
		current = next;
	}
}

void free_structure(t_command_parsing *structure)
{
	t_com_tokens *current;
	t_com_tokens *next;

	if (!structure)
		return;

	current = structure->args;
	while (current)
	{
		next = current->next;
		if (current->word) // this is key!
			free_token(current->word); // assumes free_token frees inner fields
		free(current);
		current = next;
	}
	if (structure->redirect)
		free_redirects(structure->redirect); // implement this if it's more than a flat struct
	free(structure);
}

void	free_ast(t_ast_node *ast)
{
	int	i;

	if(!ast)
		return;
	free_ast(ast->left);
	free_ast(ast->right);
	i = 0;
	if(ast->value)
	{
		while(ast->value[i])
		{
			free(ast->value[i]);
			i++;
		}
		free(ast->value);
	}
	free(ast);
}
