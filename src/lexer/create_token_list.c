/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:51:25 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/26 19:19:50 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value, t_tok_type types, t_quoted quoted)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		check_error(ENOMEM, "minishell : lexer", GENERAL);
		return (NULL);
	}
	if (value)
		new_token->expanded = ft_strdup(value);
	else
		new_token->expanded = NULL;
	if (!new_token->expanded && value)
	{
		check_error(ENOMEM, "minishell : lexer", GENERAL);
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

void	add_to_token_list(t_token_list *list, t_token *new_token)
{
	if (!list || !new_token)
		return ;
	if (!list->head)
		list->head = new_token;
	else
	{
		new_token->prev = list->tail;
		list->tail->next = new_token;
	}
	list->tail = new_token;
}

void	init_lexer_state(t_str_pos *lexer, char *line)
{
	lexer->input = line;
	lexer->start = 0;
	lexer->cur = 0;
	lexer->len = 0;
}

t_token_list	*init_token_list(void)
{
	t_token_list	*list;

	list = (t_token_list *)malloc(sizeof(t_token_list));
	if (!list)
	{
		check_error(ENOMEM, "minishell : token list", GENERAL);
		return (NULL);
	}
	list->head = NULL;
	list->tail = NULL;
	return (list);
}
