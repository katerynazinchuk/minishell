/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:58:52 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/28 18:13:31 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//static void debug_print_tokens(t_token_list *list);


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

void print_tokens(t_token_list *list)
{
	t_token *current;
	char *map[6] = {"T_WORD", "T_PIPE", "T_IN", "T_OUT", "T_APPEND", "T_HEREDOC"};

	if (!list || !list->head)
	{
		printf("No tokens to print.\n");
		return;
	}
	current = list->head;
	while (current)
	{
		printf("[%s] %s\n  ", map[current->type], current->expanded);
		print_segments(current->segment);
		printf("\n");
		current = current->next;
	}
}


///

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
		// printf("DEBUG: Current char: '%c' at position %d\n", lexer.input[lexer.current], lexer.current);
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
	// //debug_print_tokens(session->tokens);
	if(!move_to_token_expand(session->tokens))
		return (false);
	print_tokens(session->tokens);
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
			current->expanded = join_segments(current->segment);
			if(!current->expanded)
			{
				return (false);
			}
		}
		
		current = current->next;
	}
	return (true);
}

// static void debug_print_tokens(t_token_list *list)
// {
//     int tok_idx = 0;
//     for (t_token *tok = list->head; tok; tok = tok->next, tok_idx++)
//     {
//         printf("DEBUG: Token[%d] type=%d\n", tok_idx, tok->type);

//         int seg_idx = 0;
//         for (t_segment *seg = tok->segment; seg; seg = seg->next, seg_idx++)
//         {
//             printf("          Segment[%d]: value=\"%s\", expanded=\"%s\", q_type=%d\n",
//                    seg_idx,
//                    seg->value     ? seg->value     : "(null)",
//                    seg->expanded ? seg->expanded : "(null)",
//                    seg->q_type);
//         }
//         if (!tok->segment)
//         {
//             printf("          (no segments)\n");
//         }
//     }
// }
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

