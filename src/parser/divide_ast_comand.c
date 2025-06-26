/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_ast_comand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:34:04 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/26 19:38:10 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command_parsing	*extract_red_and_args(t_token *head, t_token *end)
{
	t_command_parsing	*structure;
	t_token				*current;

	if (!head || !end)
		return (NULL);
	structure = malloc(sizeof(t_command_parsing));
	if (!structure)
	{
		check_error(ENOMEM, "Command parsing ", GENERAL);
		return (NULL);
	}
	structure->redirect = NULL;
	structure->args = NULL;
	current = head;
	while (current != end)
	{
		if (current->type == T_APPEND || current->type == T_HEREDOC || \
			current->type == T_IN || current->type == T_OUT)
		{
			if (append_redirect(current, structure))
			{
				free_structure(structure);
				return (NULL);
			}
			current = current->next;
		}
		else
		{
			if (append_args(current, structure))
			{
				free_structure(structure);
				return (NULL);
			}
		}
		current = current->next;
	}
	return (structure);
}
