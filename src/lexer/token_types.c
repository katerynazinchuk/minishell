/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:42:00 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/28 17:53:33 by kzinchuk         ###   ########.fr       */
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
	new_token = create_token("|", T_PIPE);
	if (!new_token)
		return;
	// printf("DEBUG: Adding pipe token at position %d\n", lexer->current);
	add_to_token_list(list, new_token);
	lexer->current++;
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
		printf("minishell: syntax error near unexpected token `%c`\n", lexer->input[lexer->current]);
		lexer->current++;
	}
}

void create_redirection_token(t_token_list *list, char * symbol, t_tok_type type)
{
	t_token	*new_token;

	new_token = create_token(symbol, type);
	if (!new_token)
		return;
	add_to_token_list(list, new_token);
}	

void add_word_token(t_token_list *list, t_str_pos *lexer)
{
	t_token *token;

	token = create_token(NULL, T_WORD);
	if(!token)
		return ; 
	token->segment = build_segment_list(lexer);
	if(!token->segment)
	{
		free(token);
		return ;
	}
	add_to_token_list(list, token);
	lexer->current++;
}

//echo "a|b" 'c>d' "<input" >output | grep "hello|world"
//echo  a | b c>d "<input" >output | grep "hello|world"$USER'$PWD'
