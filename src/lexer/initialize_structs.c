/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:49:26 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/19 20:09:48 by tchernia         ###   ########.fr       */
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

