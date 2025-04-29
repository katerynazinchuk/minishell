/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:58:52 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/04/29 15:12:36 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list *lexer(char *line)
{
	t_token_list	*list;
	t_str_pos	*lexer;
	
	lexer = init_lexer_state();
	if (!lexer)
		return (NULL);
	list = init_token_list();
	if (!list)
		return (NULL);
	while (lexer->input[lexer->current])
	{
		if (is_whitespace(lexer->input[lexer->current]))
			skip_whitespace(lexer);
		else if (lexer->input[lexer->current] == '|"')
			add_pipe_token(list, lexer);
		else if (lexer->input[lexer->current] == '<' || lexer->input[lexer->current] == '>')
			add_redirection_token(list, lexer);
		else
			add_word_token(list, lexer);
	}
	free(lexer);
	return (list);
}


//token = extract_token(lexer, state);
//token->value = ft_substr(lexer->input, lexer->start_index, lexer->len);
//token->type = get_token_type(token->value);
//token->next = NULL;
//lexer->current_index += lexer->len;
//lexer->len = 0;
//lexer->start_index = lexer->current_index;
//lexer->input[lexer->current_index] == '\0' ? TOKEN_EOF : lexer->input[lexer->current_index];
//lexer->input[lexer->current_index] == ' ' ? TOKEN_SPACE : lexer->input[lexer->current_index];
//lexer->input[lexer->current_index] == '|' ? TOKEN_PIPE : lexer->input[lexer->current_index];
//lexer->input[lexer->current_index] == '<' ? TOKEN_REDIRECT_IN : lexer->input[lexer->current_index];
//lexer->input[lexer->current_index] == '>' ? TOKEN_REDIRECT_OUT : lexer->input[lexer->current_index];	

