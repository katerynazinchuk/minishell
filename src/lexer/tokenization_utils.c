/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:49:11 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/13 11:16:41 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

void print_tokens(t_token_list *list)
{
	t_token	*current;

	current = list->head;
	while (current)
	{
		printf("Token: [type = %d] [value = %s] [quotes = %u]\n", current->type, current->value, current->t_quote_type);
		current = current->next;
	}
}
