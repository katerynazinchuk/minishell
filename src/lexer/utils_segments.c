/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_segments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:49:00 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/26 19:23:05 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	total_length(t_segment *segments)
{
	size_t	len;

	len = 0;
	while (segments)
	{
		if (segments->value)
			len += ft_strlen(segments->value);
		segments = segments->next;
	}
	return (len);
}

int	use_quotes(t_str_pos *lexer)
{
	if (lexer->input[lexer->cur] == '"' || lexer->input[lexer->cur] == '\'')
	{
		return (1);
	}
	return (0);
}

int	check_quotes(t_str_pos *lexer)
{
	int		i;
	char	quote;

	i = lexer->cur;
	quote = lexer->input[i];
	i++;
	while (lexer->input[i])
	{
		if (lexer->input[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

t_segment	*add_quoted_segment(t_str_pos *lexer)
{
	char		quote_char;
	t_q_type	quote_type;
	char		*new_seg;
	int			len;

	quote_char = lexer->input[lexer->cur];
	if (quote_char == '"')
		quote_type = Q_DOUBLE;
	else
		quote_type = Q_SINGLE;
	lexer->cur++;
	lexer->start = lexer->cur;
	while (lexer->input[lexer->cur] && lexer->input[lexer->cur] != quote_char)
		lexer->cur++;
	len = lexer->cur - lexer->start;
	new_seg = ft_strndup(lexer->input + lexer->start, len);
	if (!new_seg)
	{
		check_error(ENOMEM, "minishell: segment", GENERAL);
		return (NULL);
	}
	if (lexer->input[lexer->cur] == quote_char)
		lexer->cur++;
	return (create_segment(new_seg, quote_type));
}

t_segment	*add_unquoted_segment(t_str_pos *lexer)
{
	int		len;
	char	*new_seg;

	lexer->start = lexer->cur;
	while (lexer->input[lexer->cur] && \
		!is_whitespace(lexer->input[lexer->cur]) && \
		!is_special_char(lexer->input[lexer->cur]) && \
		!use_quotes(lexer))
	{
		lexer->cur++;
	}
	len = lexer->cur - lexer->start;
	new_seg = ft_strndup(lexer->input + lexer->start, len);
	if (!new_seg)
	{
		check_error(ENOMEM, "minishell: segment", GENERAL);
		return (NULL);
	}
	return (create_segment(new_seg, Q_NONE));
}
