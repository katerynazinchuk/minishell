/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:42:00 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/04/30 18:24:28 by kzinchuk         ###   ########.fr       */
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
	t_token	*new_token;
	
	if(lexer->input[lexer->current] == '>' && lexer->input[lexer->current + 1] == '>')
	{
		new_token = create_token(">>", TOKEN_APPEND, QUOTE_NONE);
		if (!new_token)
			return;
		add_to_token_list(list, new_token);
		lexer->current += 2;
	}
	else if(lexer->input[lexer->current] == '<' && lexer->input[lexer->current + 1] == '<')
	{
		new_token = create_token("<<", TOKEN_HEREDOC, QUOTE_NONE);
		if (!new_token)
			return;
		add_to_token_list(list, new_token);
		lexer->current += 2;
	}
	else if(lexer->input[lexer->current] == '>')
	{
		new_token = create_token(">", TOKEN_REDIRECT_OUT, QUOTE_NONE);
		if (!new_token)
			return;
		add_to_token_list(list, new_token);
		lexer->current++;
	}
	else if(lexer->input[lexer->current] == '<')
	{
		new_token = create_token("<", TOKEN_REDIRECT_IN, QUOTE_NONE);
		if (!new_token)
			return;
		add_to_token_list(list, new_token);
		lexer->current++;
	}
}

// void add_word_token(t_token_list *list, t_str_pos *lexer)
// {
// 	t_token	*new_token;
// 	char *word;
	
// 	if (lexer->input[lexer->current] == '"' || lexer->input[lexer->current] == '\'')
// 	{
// 		return(check_quotes(lexer));
// 	}	
// 	lexer->start = lexer->current;
// 	while (lexer->input[lexer->current] &&
// 		!is_whitespace(lexer->input[lexer->current]) &&
// 		lexer->input[lexer->current] != '|' &&
// 		lexer->input[lexer->current] != '>' &&
// 		lexer->input[lexer->current] != '<' &&
// 		lexer->input[lexer->current] != '"')	
// 	{
// 		lexer->current++;
// 	}
// 	lexer->len = lexer->current - lexer->start;
// 	if (lexer->len <= 0)
// 		return;
// 	word = ft_strndup(lexer->input + lexer->start, lexer->len);
// 	if (!word)
// 		return;
// 	new_token = create_token(word, TOKEN_WORD, QUOTE_NONE);
// 	free(word);
// 	if (!new_token)
// 		return;
// 	add_to_token_list(list, new_token);
// }

void add_word_token(t_token_list *list, t_str_pos *lexer)
{
	if (use_quotes(lexer))
	{
		if (!check_quotes(lexer))
			return(no_quotes_error(lexer));
		return (add_quoted_word(list, lexer));
	}
	return (add_unquoted_word(list, lexer));
}

int use_quotes(t_str_pos *lexer)
{
	if (lexer->input[lexer->current] == '"' || lexer->input[lexer->current] == '\'')
	{
		return (1);
	}
	return (0);
}

int check_quotes(t_str_pos *lexer)
{
	int i;
	char quote;

	i = lexer->current;
	quote = lexer->input[i];
	i++;
	while(lexer->input[i])
	{
		if (lexer->input[i] == quote)
			return (1);
		i++;
	}
	return (0);
}
int no_quotes_error(t_str_pos *lexer)
{
	printf("Error: No matching quotes found for token starting at index %d\n", lexer->start);
	return (0);
}
t_token *add_quoted_word(t_token_list *list, t_str_pos *lexer)
{
	// add logic and test
	return (word_token(list, lexer, type));
}

t_token *add_unquoted_word(t_token_list *list, t_str_pos *lexer)
{
	lexer->start = lexer->current;
	while (lexer->input[lexer->current] && !is_whitespace(lexer->input[lexer->current]) &&
		lexer->input[lexer->current] != '|' && lexer->input[lexer->current] != '>' &&
		lexer->input[lexer->current] != '<' && lexer->input[lexer->current] != '"' &&
		lexer->input[lexer->current] != '\'')
	{
		lexer->current++;
	}
	return(word_token(list, lexer, QUOTE_NONE));
}
t_token * word_token (t_token_list *list, t_str_pos *lexer, t_quote_type quote)
{
	t_token	*new_token;
	char	*word;
	int		start;

	start = lexer->current;
	lexer->len = lexer->current - lexer->start;
	word = ft_strndup(lexer->input + start, lexer->len);
	if (!word)
		return (NULL);
	new_token = create_token(word, TOKEN_WORD, QUOTE_NONE);
	free(word);
	if (!new_token)
		return (NULL);
	add_to_token_list(list, new_token);
	return (new_token);
}
	
