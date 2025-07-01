/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:49:26 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/01 11:53:49 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_segment_list(t_segment *head)
{
	t_segment	*current;
	t_segment	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->expanded)
		free(token->expanded);
	if (token->segment)
		free_segment_list(token->segment);
	free(token);
}

void	free_token_list(t_token_list *list)
{
	t_token	*current;
	t_token	*next;

	if (!list)
		return ;
	current = list->head;
	while (current)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
	free(list);
}
