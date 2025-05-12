/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:51:25 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/12 15:24:25 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_token *create_token(char *value, t_token_type types, t_quote_type quotes)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if(!new_token)
	return (NULL);
	new_token->value = ft_strdup(value);
	if(!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->bad_subs = 0;
	new_token->type = types;
	new_token->q_type = quotes;
	new_token->next = NULL;
	return (new_token);
}

void add_to_token_list(t_token_list *list, t_token *new_token)
{
	if (!list || !new_token)
	return;
	if (!list->head)
	list->head = new_token;
	else
	list->tail->next = new_token;
	list->tail = new_token;
}

void free_token(t_token *token)
{
	if (token)
	{
		free(token->value);
		if (token->expanded)
			free(token->expanded);
		free(token);
	}
}

void free_token_list(t_token_list *list)
{
	t_token	*current;
	t_token	*next;

	if (!list)
		return;
	current = list->head;
	while (current)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
	free(list);
}