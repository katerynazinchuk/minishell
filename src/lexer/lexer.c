/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:58:52 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/23 19:12:56 by tchernia         ###   ########.fr       */
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

/* t_token_list *fill_tokens(char *line)
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
} */

int fill_tokens(char *line, t_token_list **tokens)
{
	t_token_list	*list;
	t_token			*eof;
	t_str_pos		lexer;
	
	list = init_token_list();
	if (!list)
		return (check_error(ENOMEM, "create tokens", GENERAL));
	init_lexer_state(&lexer, line);
	while (lexer.input[lexer.current])//str[i]
	{
		if (is_whitespace(lexer.input[lexer.current]))
			skip_whitespace(&lexer);
		else if (lexer.input[lexer.current] == '|')
		{
			if (add_pipe_token(list, &lexer))
				return (1);
		}
		else if (lexer.input[lexer.current] == '<' \
			|| lexer.input[lexer.current] == '>')
			add_redirection_token(list, &lexer);
		else if(add_word_token(list, &lexer))
		{
			free_token_list(list);
			return (check_error(ENOMEM, "create tokens", GENERAL));
		}
	}
	eof = create_token("eof", T_EOF, UNQUOTED);
	if (!eof)
	{
		free_token_list(list);
		return (check_error(ENOMEM, "create tokens", GENERAL));
	}
	add_to_token_list(list, eof);
	*tokens = list;
	return (0);
}

int	lexer(t_session *session)
{
	if (fill_tokens(session->line, &session->tokens))
		return (1);
	if (!session->tokens)
		return (1);
	// free_segment_list(session->tokens->head->segment);
	
	if (expand_segments(session))
	{
		// free_token_list(session->tokens); level up free
		return (1);
	}
	if(move_to_token_expand(session->tokens))
		return (1);
	//print_tokens(session->tokens);
	return (0);
}

int	move_to_token_expand(t_token_list *list)
{
	t_token *current;

	current = list->head;
	while(current)
	{
		if (!current->expanded)
		{
			current->expanded = join_segments(current->segment, &current->quoted);
			if(!current->expanded)
				return (check_error(ENOMEM, "create tokens", GENERAL));
		}
		current = current->next;
	}
	return (0);
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

