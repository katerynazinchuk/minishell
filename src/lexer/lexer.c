/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:58:52 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/24 13:37:28 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int fill_tokens(char *line, t_token_list **tokens)
{
	t_token_list	*list;
	t_token			*eof;
	t_str_pos		lexer;
	
	list = init_token_list();
	if (!list)
		return (check_error(ENOMEM, "create tokens", GENERAL));
	init_lexer_state(&lexer, line);
	while (lexer.input[lexer.current])//str[i]
	{
		if (is_whitespace(lexer.input[lexer.current]))
			skip_whitespace(&lexer);
		else if (lexer.input[lexer.current] == '|')
		{
			if (add_pipe_token(list, &lexer))
				return (1);
		}
		else if (lexer.input[lexer.current] == '<' \
			|| lexer.input[lexer.current] == '>')
			add_redirection_token(list, &lexer);
		else if(add_word_token(list, &lexer))
		{
			free_token_list(list);
			return (check_error(ENOMEM, "create tokens", GENERAL));
		}
	}
	eof = create_token("eof", T_EOF, UNQUOTED);
	if (!eof)
	{
		free_token_list(list);
		return (check_error(ENOMEM, "create tokens", GENERAL));
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
	if(move_to_token_expand(session->tokens))
		return (1);
	//print_tokens(session->tokens);
	return (0);
}



