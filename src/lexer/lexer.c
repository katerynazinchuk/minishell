/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:58:52 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/01 17:51:07 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redirection_char(char c)
{
	return (c == '<' || c == '>');
}

void	skip_whitespace(t_str_pos *lexer)
{
	while (lexer->input[lexer->cur] && is_whitespace(lexer->input[lexer->cur]))
		lexer->cur++;
}

int	fill_tokens(char *line, t_token_list **tokens)
{
	t_token_list	*list;
	t_str_pos		lexer;

	list = init_token_list();
	if (!list)
		return (1);
	init_lexer_state(&lexer, line);
	while (lexer.input[lexer.cur])
	{
		if (is_whitespace(lexer.input[lexer.cur]))
			skip_whitespace(&lexer);
		else if (lexer.input[lexer.cur] == '|')
			add_pipe_token(list, &lexer);
		else if (is_redirection_char(lexer.input[lexer.cur]))
			add_red_token(list, &lexer);
		else if (add_word_token(list, &lexer))
			free_token_list(list);
		if (errno == ENOMEM)
			return (1);
	}
	if (add_eof_token(list))
		return (1);
	*tokens = list;
	return (0);
}

int	lexer(t_session *session)
{
	if (fill_tokens(session->line, &session->tokens))
		return (1);
	if (!session->tokens)
		return (1);
	if (expand_segments(session))
	{
		if ()
			check_error(BAD_SUBS, seg->value, GENERAL);
		esle 
			check_error(ENOMEM, "expand segmants", GENERAL);
		return (1);
	}
	if (move_to_token_expand(session->tokens))
		return (1);
	return (0);
}
