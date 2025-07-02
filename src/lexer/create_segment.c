/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_segment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:20:35 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/02 13:38:56 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_segment	*create_segment(char *value, t_q_type q_type)
{
	t_segment	*segment;

	segment = malloc(sizeof(t_segment));
	if (!segment)
	{
		check_error(ENOMEM, "segment", GENERAL);
		return (NULL);
	}
	segment->value = value;
	segment->q_type = q_type;
	segment->next = NULL;
	return (segment);
}

void	append_segment(t_segment **head, t_segment *new_seg)
{
	t_segment	*current;

	if (!*head)
	{
		*head = new_seg;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_seg;
}

t_segment	*build_segment_list(t_str_pos *lexer)
{
	t_segment	*head;
	t_segment	*new_seg;

	head = NULL;
	while (lexer->input[lexer->cur] &&\
!is_whitespace(lexer->input[lexer->cur]) &&\
!ft_strchr("|<>", lexer->input[lexer->cur]))
	{
		if (use_quotes(lexer))
		{
			if (!check_quotes(lexer))
			{
				check_error(SYNTAX_ERR, "no matching quotes", GENERAL);
				return (NULL);
			}
			new_seg = add_quoted_segment(lexer);
		}
		else
			new_seg = add_unquoted_segment(lexer);
		if (!new_seg)
			return (NULL);
		append_segment(&head, new_seg);
	}
	return (head);
}

int	join_segments(t_segment *seg, t_quoted *quoted, char **expanded)
{
	size_t	total_len;
	char	*result;

	result = NULL;
	*quoted = UNQUOTED;
	total_len = total_length(seg);
	if (total_len > 0 || seg->q_type == Q_SINGLE || seg->q_type == Q_DOUBLE)
	{
		result = ft_calloc(sizeof(char), total_len + 1);
		if (!result)
			return (check_error(ENOMEM, "create tokens", GENERAL));
	}
	while (seg && total_len)
	{
		if (seg->q_type == Q_SINGLE || seg->q_type == Q_DOUBLE)
			*quoted = QUOTED;
		if (seg->value)
			ft_strlcat(result, seg->value, total_len + 1);
		seg = seg->next;
	}
	*expanded = result;
	return (0);
}

int	move_to_token_expand(t_token_list *list)
{
	t_token	*cur;

	cur = list->head;
	while (cur)
	{
		if (!cur->expanded)
		{
			if (join_segments(cur->segment, &cur->quoted, &cur->expanded))
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}
