/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:58:52 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/09 15:50:30 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_segments(t_segment *segment)
{
	t_segment *current;

	if (!segment)
		return;
	current = segment;
	while (current)
	{
		printf("%s ", current->value);

		current = current->next;
	}
}

// void print_tokens(t_token_list *list)
// {
// 	t_token *current;
// 	char *map[7] = {"T_WORD", "T_PIPE", "T_IN", "T_OUT", "T_APPEND", "T_HEREDOC", "T_EOF"};

// 	if (!list || !list->head)
// 	{
// 		printf("No tokens to print.\n");
// 		return;
// 	}
// 	current = list->head;
// 	while (current)
// 	{
// 		printf("[%s] %s\n  ", map[current->type], current->expanded);
// 		print_segments(current->segment);
// 		printf("\n");
// 		current = current->next;
// 	}
// }

t_token_list *fill_tokens(char *line)
{
	t_token_list	*list;
	t_token			*eof;
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
		else if(!add_word_token(list, &lexer))
		{
			free_token_list(list);
			return (NULL);
		}
	}
	eof = create_token("eof", T_EOF, UNQUOTED);
	if (!eof)
	{
		free_token_list(list);
		return (NULL);
	}
	add_to_token_list(list, eof);
	return (list);
}

bool	lexer(t_session *session)
{
	session->tokens = fill_tokens(session->line);
	if (!session->tokens)
		return (false);
	// free_segment_list(session->tokens->head->segment);
	
	if (!expand_segments(session))
	{
		// if (session->tokens->error == 1)//bad_subs
		// 	bad_subs_error();//syntax error {{}}
		//else
			//malloc_error(&session->shell->last_exit_status);
		free_token_list(session->tokens);
		return (false);//malloc 
	}
	if(!move_to_token_expand(session->tokens))
		return (false);
	//print_tokens(session->tokens);
	return (true);
}

bool	move_to_token_expand(t_token_list *list)
{
	t_token *current;

	current = list->head;
	while(current)
	{
		if (!current->expanded)
		{
			current->expanded = join_segments(current->segment, &current->quoted);
			if(!current->expanded)
				return (false);
		}
		current = current->next;
	}
	return (true);
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

