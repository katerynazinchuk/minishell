/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:58:52 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/25 18:11:15 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redirection_char(char c)
{
	return (c == '<' || c == '>');
}

int	fill_tokens(char *line, t_token_list **tokens)
{
	t_token_list	*list;
	t_token			*eof;
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
	eof = create_token("EOF", T_EOF, UNQUOTED);
	if (!eof)
	{
		free_token_list(list);
		return (1);
	}
	add_to_token_list(list, eof);
	*tokens = list;
	return (0);
}



int	lexer(t_session *session)
{
	if (fill_tokens(session->line, &session->tokens))
		return (1);
	if (!session->tokens)
		return (1);
	// free_segment_list(session->tokens->head->segment);
	if (expand_segments(session))
	{
		// free_token_list(session->tokens); level up free
		return (1);
	}
	if (move_to_token_expand(session->tokens))
		return (1);
	//print_tokens(session->tokens);
	return (0);
}
