/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:52:33 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/01 16:07:46 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "token.h"

typedef struct s_str_pos
{
	char		*input;
	int			start;
	int			cur;
	size_t		len;
}	t_str_pos;

/* -------------------------------------------------------------------------- */

t_token			*create_token(char *value, t_tok_type types, t_quoted quoted);
void			add_to_token_list(t_token_list *list, t_token *new_token);
void			free_token(t_token *token);
void			free_token_list(t_token_list *list);
void			free_segment_list(t_segment *head);

/* -------------------------------------------------------------------------- */

void			init_lexer_state(t_str_pos *lexer, char *line);
t_token_list	*init_token_list(void);

/* -------------------------------------------------------------------------- */

t_segment		*create_segment(char *value, t_q_type q_type);
void			append_segment(t_segment **head, t_segment *new_seg);
t_segment		*build_segment_list(t_str_pos *lexer);
size_t			total_length(t_segment *segments);
int				join_segments(t_segment *segment, t_quoted *quoted,\
														char **expanded);

/* -------------------------------------------------------------------------- */

void			skip_whitespace(t_str_pos *lexer);
int				add_pipe_token(t_token_list *list, t_str_pos *lexer);
void			add_red_token(t_token_list *list, t_str_pos *lexer);
int				create_red_token(t_token_list *list, char *symbol,\
												t_tok_type type);
int				add_word_token(t_token_list *list, t_str_pos *lexer);
int				add_eof_token(t_token_list *list);

/* -------------------------------------------------------------------------- */

int				fill_tokens(char *line, t_token_list **tokens);
int				lexer(t_session *session);
int				move_to_token_expand(t_token_list *list);
void			print_tokens(t_token_list *list);

/* -------------------------------------------------------------------------- */

int				use_quotes(t_str_pos *lexer);
int				check_quotes(t_str_pos *lexer);
t_segment		*add_quoted_segment(t_str_pos *lexer);
t_segment		*add_unquoted_segment(t_str_pos *lexer);

#endif