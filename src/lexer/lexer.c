/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:58:52 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/27 15:09:22 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list *fill_tokens(char *line)
{
	t_token_list	*list;
	t_str_pos		lexer;
	
	list = init_token_list();
	if (!list)
		return (NULL);
	init_lexer_state(&lexer, line);
	while (lexer.input[lexer.current])//str[i]
	{
		if (is_whitespace(lexer.input[lexer.current]))
			skip_whitespace(&lexer);
		else if (lexer.input[lexer.current] == '|')
			add_pipe_token(list, &lexer);
		else if (lexer.input[lexer.current] == '<' \
			|| lexer.input[lexer.current] == '>')
			add_redirection_token(list, &lexer);
		else
			add_word_token(list, &lexer);
	}
	return (list);
}

bool	lexer(t_session *session)
{
	session->tokens = fill_tokens(session->line);
	if (!session->tokens)
		return (false);
	if (!expand_tokens(session))
		return (false);
	if(!move_to_token_expand(session->tokens))
		return (false);
	return (true);
}

bool	move_to_token_expand(t_token_list *list)
{
	t_token *current;

	current = list->head;
	while(current)
	{
		current->expanded = join_segments(current->segment);
		if(!current->expanded)
			return (false);
		current = current->next;
	}
	return (true);
}


/* t_token_list	*lexer(t_shell *shell)
{
	shell->tokens = fill_tokens(shell->line);
	expand_tokens(shell);//move it to fill_tokens
	return(shell->tokens);
} */



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

