/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:20:35 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/27 15:23:31 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_segment *create_segment(char *value, t_q_type q_type)
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
		!is_special_char(lexer->input[lexer->current]))
	{
		if(use_quotes(lexer))
		{
			if(!check_quotes(lexer))
			{
				quotes_error(lexer);
				// lexer->current++;
				break;
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

size_t total_length(t_segment *segments)
{
	size_t len;

	len = 0;
	while(segments)
	{
		if(segments->expanded)
			len +=ft_strlen(segments->expanded);
		segments = segments->next;
	}
	return (len);
}

char *join_segments(t_segment *segment)
{
	size_t total_len;
	size_t seg_len;
	t_segment *cur;
	char *result;
	char *write_ptr;

	total_len = total_length(segment);
	result = malloc(total_len + 1);
	if(!result)
		return (NULL);
	write_ptr = result;
	cur = segment;
	while(cur)
	{
		if(cur->expanded)
		{
			seg_len = ft_strlen(cur->expanded);
			ft_memcpy(write_ptr, cur->expanded, seg_len);
			write_ptr += seg_len;
		}
		cur = cur->next;
	}
	*write_ptr = '\0';
	return(result);
}
