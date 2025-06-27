/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:00:29 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/27 18:02:20 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirects(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	current = redir;
	while (current)
	{
		next = current->next;
		free(current->connection);
		free(current);
		current = next;
	}
}

void	free_structure(t_command_parsing *structure)
{
	t_com_tokens	*current;
	t_com_tokens	*next;

	if (!structure)
		return ;
	current = structure->args;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	// if (structure->redirect)
	// 	free_redirects(structure->redirect);
	free(structure);
}

void	free_ast(t_ast_node **ast)
{
	int	i;

	if (!ast || !*ast)
		return ;
	free_ast(&(*ast)->left);
	free_ast(&(*ast)->right);
	i = 0;
	if ((*ast)->value)
	{
		while ((*ast)->value[i])
		{
			free((*ast)->value[i]);
			i++;
		}
		free((*ast)->value);
	}
	if ((*ast)->redir)
		free_redirects((*ast)->redir);
	free((*ast));
	*ast = NULL;
}
