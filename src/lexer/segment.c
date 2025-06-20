/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:20:35 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/20 19:08:53 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_segment *create_segment(char *value, t_q_type q_type)
{
	t_segment *segment = malloc(sizeof(t_segment));
	if(!segment)
	{
		check_error(ENOMEM, "minishell : segment");
		return (NULL);
	}
	segment->value = value;
	segment->q_type = q_type;
	segment->next = NULL;
	return (segment);
}

void append_segment(t_segment **head, t_segment *new_seg)
{
	t_segment *current;

	if(!*head)
	{
		*head = new_seg;
		return;
	}
	current = *head;
	while(current->next)
		current = current->next;
	current->next = new_seg;
}

t_segment *build_segment_list(t_str_pos *lexer)
{
	t_segment *head;
	t_segment *new_seg;

	head = NULL;	
	while(lexer->input[lexer->current] &&
		!is_whitespace(lexer->input[lexer->current]) &&
		!ft_strchr("|<>", lexer->input[lexer->current]))
	{
		if(use_quotes(lexer))
		{
			if(!check_quotes(lexer))
			{
				check_error(SYNTAX_ERROR, "No matching quotes");
				return (NULL);
			}
			new_seg = add_quoted_segment(lexer);
		}
		else
			new_seg = add_unquoted_segment(lexer);
		if(!new_seg)
			return (NULL);
		append_segment(&head, new_seg);
	}
	return (head);
}

char *join_segments(t_segment *segment, t_quoted *quoted)
{
	size_t total_len;
	char *result;

	*quoted = UNQUOTED;
	total_len = total_length(segment);
	if(total_len == 0)
		return(ft_strdup(""));
	result = malloc(total_len + 1);
	if(!result)
		return (NULL);
	result[0] = '\0';
	while(segment)
	{
		if(segment->q_type == Q_SINGLE || segment->q_type == Q_DOUBLE)
			*quoted = QUOTED;
		if(segment->value)
			ft_strlcat(result, segment->value, total_len + 1);
		segment = segment->next;
	}
	return (result);
}
