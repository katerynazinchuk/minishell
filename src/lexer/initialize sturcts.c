/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize sturcts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:49:26 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/04/29 14:52:11 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_str_pos *init_lexer_state(void)
{
	t_str_pos	*lexer;
	lexer = (t_str_pos *)malloc(sizeof(t_str_pos));
	if (!lexer)
		return (NULL);

	lexer->input = NULL;
	lexer->start = 0;
	lexer->current = 0;
	lexer->len = 0;
	return (lexer);
}

t_token_list *init_token_list(void)
{
	t_token_list	*list;
	
	list = (t_token_list *)malloc(sizeof(t_token_list));
	if (!list)
	return (NULL);
	list->head = NULL;
	list->tail = NULL;
	return (list);
}
