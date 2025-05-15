/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:49:11 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/15 17:55:18 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}
int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '"');
}

void print_tokens(t_token_list *list, t_env_list *env_list)
{
	t_token	*current;

	current = list->head;
	expand_tokens(list, env_list);
	while (current)
	{
		printf("Token: [type = %d] [value = %s] [expanded = %s][quotes = %u]\n", current->type, current->value, current->expanded, current->q_type);
		current = current->next;
	}
}
