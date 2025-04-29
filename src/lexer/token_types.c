/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:42:00 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/04/29 15:29:49 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char *ft_strndup(const char *s, size_t n)
{
    char    *new_str;
    size_t  i;

    new_str = (char *)malloc(sizeof(char) * (n + 1));
    if (!new_str)
        return (NULL);
    i = 0;
    while (i < n && s[i])
    {
        new_str[i] = s[i];
        i++;
    }
    new_str[i] = '\0';
    return (new_str);
}

void skip_whitespace(t_str_pos *lexer)
{
	while(lexer->input[lexer->current] && is_whitespace(lexer->input[lexer->current]))
		lexer->current++;
}

void add_pipe_token(t_token_list *list, t_str_pos *lexer)
{
	t_token	*new_token;
	new_token = create_token("|", TOKEN_PIPE);
	if (!new_token)
		return;
	add_to_token_list(list, new_token);
	lexer->current++;
	lexer->len++;
}

void add_redirection_token(t_token_list *list, t_str_pos *lexer)
{
	t_token	*new_token;
	
	if(lexer->input[lexer->current] == '>' && lexer->input[lexer->current + 1] == '>')
	{
		new_token = create_token(">>", TOKEN_APPEND);
		if (!new_token)
			return;
		add_to_token_list(list, new_token);
		lexer->current += 2;
	}
	else if(lexer->input[lexer->current] == '<' && lexer->input[lexer->current + 1] == '<')
	{
		new_token = create_token("<<", TOKEN_HEREDOC);
		if (!new_token)
			return;
		add_to_token_list(list, new_token);
		lexer->current += 2;
	}
	else if(lexer->input[lexer->current] == '>')
	{
		new_token = create_token(">", TOKEN_REDIRECT_OUT);
		if (!new_token)
			return;
		add_to_token_list(list, new_token);
		lexer->current++;
	}
	else if(lexer->input[lexer->current] == '<')
	{
		new_token = create_token("<", TOKEN_REDIRECT_IN);
		if (!new_token)
			return;
		add_to_token_list(list, new_token);
		lexer->current++;
	}
}

void add_word_token(t_token_list *list, t_str_pos *lexer)
{
	t_token	*new_token;
	char *word;
	
	lexer->start = lexer->current;
	while (lexer->input[lexer->current] &&
		!is_whitespace(lexer->input[lexer->current]) &&
		lexer->input[lexer->current] != '|' &&
		lexer->input[lexer->current] != '>' &&
		lexer->input[lexer->current] != '<')
	{
		lexer->current++;
	}
	lexer->len = lexer->current - lexer->start;
	if (lexer->len <= 0)
		return;
	word = ft_strndup(lexer->input + lexer->start, lexer->len);
	if (!word)
		return;
	new_token = create_token(word, TOKEN_WORD);
	if (!new_token)
		return;
	new_token->value = word;
	add_to_token_list(list, new_token);
}
