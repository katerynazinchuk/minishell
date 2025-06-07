/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:51:46 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/02 15:51:59 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void print_tokens(t_session *session)
// {
// 	t_token	*current;

// 	current = session->tokens->head;
// 	while (current)
// 	{
// 		printf("Token: [type = %d] [expanded = %s]\n", current->type, current->expanded);
// 		current = current->next;
// 	}
// }

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