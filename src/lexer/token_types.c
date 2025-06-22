/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:42:00 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/22 17:57:09 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void skip_whitespace(t_str_pos *lexer)
{
	while(lexer->input[lexer->current] && is_whitespace(lexer->input[lexer->current]))
		lexer->current++;
}

int add_pipe_token(t_token_list *list, t_str_pos *lexer)
{
	t_token	*new_token;
	new_token = create_token("|", T_PIPE, UNQUOTED);
	if (!new_token)
		return (check_error(ENOMEM, "create token", GENERAL));
	add_to_token_list(list, new_token);//TODO check !!!
	lexer->current++;
	return (0);
}

void add_redirection_token(t_token_list *list, t_str_pos *lexer)
{
	if (lexer->input[lexer->current + 1] == '>' && lexer->input[lexer->current] == '>')
	{
		create_redirection_token(list, ">>", T_APPEND);
		lexer->current += 2;
	}
	else if (lexer->input[lexer->current + 1] == '<' && lexer->input[lexer->current] == '<')
	{
		create_redirection_token(list, "<<", T_HEREDOC);
		lexer->current += 2;
	}
	else if (lexer->input[lexer->current] == '>')
	{
		create_redirection_token(list, ">", T_OUT);
		lexer->current++;
	}
	else if (lexer->input[lexer->current] == '<')
	{
		create_redirection_token(list, "<", T_IN);
		lexer->current++;
	}
	else 
	{
		check_error(TOKEN_ERROR, &lexer->input[lexer->current], GENERAL);//TODO test case
		// printf("minishell: syntax error near unexpected token `%c`\n", lexer->input[lexer->current]);
		lexer->current++;
	}
}

void create_redirection_token(t_token_list *list, char * symbol, t_tok_type type)
{
	t_token	*new_token;

	new_token = create_token(symbol, type, UNQUOTED);
	if (!new_token)
		return;
	add_to_token_list(list, new_token);
}	

bool add_word_token(t_token_list *list, t_str_pos *lexer)
{
	t_token *token;

	token = create_token(NULL, T_WORD, UNQUOTED);
	if(!token)
		return (false);
	token->segment = build_segment_list(lexer);//TODO what kind or errors are here?
	if(!token->segment)
	{
		free(token);
		return (false);
	}
	add_to_token_list(list, token);
	return (true);
}

//echo "a|b" 'c>d' "<input" >output | grep "hello|world"
//echo  a | b c>d "<input" >output | grep "hello|world"$USER'$PWD'
