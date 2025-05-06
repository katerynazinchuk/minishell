/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:58:52 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/06 18:59:54 by tchernia         ###   ########.fr       */
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
		else if (lexer.input[lexer.current] == '<' || lexer.input[lexer.current] == '>')
			add_redirection_token(list, &lexer);
		else
			add_word_token(list, &lexer);
	}
	return (list);
}

void	*expand_tokens(t_shell_type *shell)
{
	t_token_type	*current;

	current = shell->token_list->head;
	while(!current)
	{
		if (ft_strchr(current->value), '$')
		{
			if (current->q_type != "QUOTE_SINGLE")
				{
					update_value(current->value, shell->env_list);
				}
		}
		current->head->next;
	}
}

void	update_value(char *str, t_env_list *env_list)
{
	if (*(ft_strchr(str, $) + 1) == '_' || is_alpha())
}

t_token_list	*lexer(char *line, t_shell_type *shell)
{
	shell->token_list = fill_tokens(line);
	expand_tokens(shell);
	return(shell->token_list);
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

