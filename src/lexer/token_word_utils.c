/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:49:00 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/15 17:54:08 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static t_token	*word_token (t_token_list *list, t_str_pos *lexer, t_quote_type quote_type);

int	use_quotes(t_str_pos *lexer)
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

t_token *add_quoted_word(t_token_list *list, t_str_pos *lexer)
{
	char quote_char;
	t_quote_type quote_type;
	t_token *new_token;

	quote_char = lexer->input[lexer->current];
	if(quote_char == '"')
		quote_type = QUOTE_DOUBLE;
	else
		quote_type = QUOTE_SINGLE;
	lexer->current++;
	//we changed mind cause of heredoc (need to expand lexer->input)
	lexer ->start = lexer->current;
	while(lexer->input[lexer->current] && lexer->input[lexer->current] != quote_char)
	{
		lexer->current++;
	}
	new_token = word_token(list, lexer, quote_type);
	if (lexer->input[lexer->current] == quote_char)
		lexer->current++;
	return (new_token);
}

t_token *add_unquoted_word(t_token_list *list, t_str_pos *lexer)
{
	lexer->start = lexer->current;
	while (lexer->input[lexer->current] &&
		!is_whitespace(lexer->input[lexer->current]) &&
		!is_special_char(lexer->input[lexer->current]))
	{
		lexer->current++;
	}
	//we changed mind cause of heredoc (need to expand lexer->input)
	return(word_token(list, lexer, QUOTE_NONE));
}

static t_token *word_token (t_token_list *list, t_str_pos *lexer, t_quote_type quote_type)
{
	t_token	*new_token;
	char	*word;

	lexer->len = lexer->current - lexer->start;
	word = ft_strndup(lexer->input + lexer->start, lexer->len);//int checged to long
	if (!word)
		return (NULL);
	new_token = create_token(word, TOKEN_WORD, quote_type);
	free(word);
	if (!new_token)
		return (NULL);
	add_to_token_list(list, new_token);
	return (new_token);
}
