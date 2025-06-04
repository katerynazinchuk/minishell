/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:51:25 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/04 13:34:28 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *create_token(char *value, t_tok_type types, t_quoted quoted)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if(!new_token)
		return (NULL);
	new_token->expanded = value ? ft_strdup(value) : NULL;//rewrite for if or while cant use ternary
	if (!new_token->expanded && value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->bad_subs = 0;
	new_token->type = types;
	new_token->quoted = quoted;
	new_token->segment = NULL;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void add_to_token_list(t_token_list *list, t_token *new_token)
{
	if (!list || !new_token)
		return;
	if (!list->head)
		list->head = new_token;
	else
	{
		new_token->prev = list->tail;
		list->tail->next = new_token;
	}
	list->tail = new_token;
}

void free_segment_list(t_segment *head)
{
	t_segment *current;
	t_segment *next;
	current = head;

	while(current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
void free_token(t_token *token)
{
	if (!token)
		return;
	if (token->expanded)
		free(token->expanded);
	if(token->segment)
		free_segment_list(token->segment);
	free(token);
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