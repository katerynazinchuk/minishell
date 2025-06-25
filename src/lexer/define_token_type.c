/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_token_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:42:00 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/25 18:14:52 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespace(t_str_pos *lexer)
{
	while (lexer->input[lexer->cur] && is_whitespace(lexer->input[lexer->cur]))
		lexer->cur++;
}

int	add_pipe_token(t_token_list *list, t_str_pos *lexer)
{
	t_token	*new_token;

	new_token = create_token("|", T_PIPE, UNQUOTED);
	if (!new_token)
		return (1);
	add_to_token_list(list, new_token);
	lexer->cur++;
	return (0);
}

void	add_red_token(t_token_list *list, t_str_pos *lexer)//change to int
{
	if (lexer->input[lexer->cur + 1] == '>' && lexer->input[lexer->cur] == '>')
	{
		create_red_token(list, ">>", T_APPEND);
		lexer->cur += 2;
	}
	else if (lexer->input[lexer->cur + 1] == '<' && lexer->input[lexer->cur] == '<')
	{
		create_red_token(list, "<<", T_HEREDOC);
		lexer->cur += 2;
	}
	else if (lexer->input[lexer->cur] == '>')
	{
		create_red_token(list, ">", T_OUT);
		lexer->cur++;
	}
	else if (lexer->input[lexer->cur] == '<')
	{
		create_red_token(list, "<", T_IN);
		lexer->cur++;
	}
	else
		lexer->cur++;
}

int	create_red_token(t_token_list *list, char *symbol, t_tok_type type)
{
	t_token	*new_token;

	new_token = create_token(symbol, type, UNQUOTED);
	if (!new_token)
		return (1);
	add_to_token_list(list, new_token);
	return (0);
}

int	add_word_token(t_token_list *list, t_str_pos *lexer)
{
	t_token	*token;

	token = create_token(NULL, T_WORD, UNQUOTED);
	if (!token)
		return (1);
	token->segment = build_segment_list(lexer);
	if (!token->segment)
	{
		free(token);
		return (1);
	}
	add_to_token_list(list, token);
	return (0);
}

int	add_eof_token(t_token_list *list)
{
	t_token	*eof;

	eof = create_token("EOF", T_EOF, UNQUOTED);
	if (!eof)
	{
		free_token_list(list);
		return (1);
	}
	add_to_token_list(list, eof);
	return (0);
}
