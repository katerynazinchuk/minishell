/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:49:11 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/27 15:14:36 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '"');
}

void print_tokens(t_session *session)
{
	t_token	*current;

	current = session->tokens->head;
	while (current)
	{
		printf("Token: [type = %d] [value = %s] [expanded = %s]\n", current->type, current->value, current->expanded);
		current = current->next;
	}
}

// void print_tokens(t_token_list *list, t_env_list *env_list)
// {
// 	t_token	*current;

// 	current = list->head;
// 	expand_tokens(list, env_list);
// 	while (current)
// 	{
// 		printf("Token: [type = %d] [value = %s] [expanded = %s][quotes = %u]\n", current->type, current->value, current->expanded, current->q_type);
// 		current = current->next;
// 	}
// }
