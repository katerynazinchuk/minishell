/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:49:26 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/26 15:32:09 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_lexer_state(t_str_pos *lexer, char *line)
{
	lexer->input = line;
	lexer->start = 0;
	lexer->current = 0;
	lexer->len = 0;
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

t_segment *init_segment(char *value, t_q_type q_type)
{
	t_segment *segment = malloc(sizeof(t_segment));
	if(!segment)
		return (NULL);
	segment->value = value;
	segment->expanded = NULL;
	segment->q_type = q_type;
	segment->next = NULL;
	return (segment);
}
