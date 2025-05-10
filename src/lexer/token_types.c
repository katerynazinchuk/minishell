/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:42:00 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/10 08:35:53 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void skip_whitespace(t_str_pos *lexer)
{
	while(lexer->input[lexer->current] && is_whitespace(lexer->input[lexer->current]))
		lexer->current++;
}

void add_pipe_token(t_token_list *list, t_str_pos *lexer)
{
	t_token	*new_token;
	new_token = create_token("|", TOKEN_PIPE, QUOTE_NONE);
	if (!new_token)
		return;
	add_to_token_list(list, new_token);
	lexer->current++;
}

void add_redirection_token(t_token_list *list, t_str_pos *lexer)
{
	if (lexer->input[lexer->current + 1] == '>' && lexer->input[lexer->current] == '>')
	{
		create_redirection_token(list, ">>", TOKEN_APPEND);
		lexer->current += 2;
	}
	else if (lexer->input[lexer->current + 1] == '<' && lexer->input[lexer->current] == '<')
	{
		create_redirection_token(list, "<<", TOKEN_HEREDOC);
		lexer->current += 2;
	}
	else if (lexer->input[lexer->current] == '>')
	{
		create_redirection_token(list, ">", TOKEN_REDIRECT_OUT);
		lexer->current++;
	}
	else if (lexer->input[lexer->current] == '<')
	{
		create_redirection_token(list, "<", TOKEN_REDIRECT_IN);
		lexer->current++;
	}
	else 
	{
		printf("minishell: syntax error near unexpected token `%c`\n", lexer->input[lexer->current]);
		lexer->current++;
	}
}

void create_redirection_token(t_token_list *list, char *symbol, t_token_type type)
{
	t_token	*new_token;

	new_token = create_token(symbol, type, QUOTE_NONE);
	if (!new_token)
		return;
	add_to_token_list(list, new_token);
}	

void add_word_token(t_token_list *list, t_str_pos *lexer)
{
	printf("add word token : check quotes: %s   -> position: %ld\n", lexer->input, lexer->current);

	if (use_quotes(lexer))
	{
		if (!check_quotes(lexer))
		{
			quotes_error(lexer);
			//exit (1);
			lexer->current++;
			return;
			//figure out what better use return or exit, and on which cases what?
		}
		add_quoted_word(list, lexer);
		return;
	}
	add_unquoted_word(list, lexer);
}

//echo "a|b" 'c>d' "<input" >output | grep "hello|world"
