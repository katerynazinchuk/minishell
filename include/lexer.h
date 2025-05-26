/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:52:33 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/26 15:32:25 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "token.h"

//help track the current position in the string, if we have multiple tokens
typedef struct s_str_pos
{
	char	*input;
	int		start;
	int		current;
	size_t		len;
}	t_str_pos;


int				is_whitespace(char c);
int				is_special_char(char c);
char			*ft_strndup(const char *s, size_t n);

t_token 		*create_token(char *value, t_tok_type types, t_q_type quotes);
void			add_to_token_list(t_token_list *list, t_token *new_token);
void			free_token(t_token *token);
void			free_token_list(t_token_list *list);

void			init_lexer_state(t_str_pos *lexer, char *line);
t_token_list	*init_token_list(void);
t_segment		*init_segment(char *value, t_q_type q_type);

void			skip_whitespace(t_str_pos *lexer);
void			add_pipe_token(t_token_list *list, t_str_pos *lexer);
void			add_redirection_token(t_token_list *list, t_str_pos *lexer);
void			create_redirection_token(t_token_list *list, char *symbol, t_tok_type type);
void			add_word_token(t_token_list *list, t_str_pos *lexer);

t_token_list	*fill_tokens(char *line);
//t_token_list	*lexer(t_shell *shell);
void			print_tokens(t_shell *shell);

int 			use_quotes(t_str_pos *lexer);
int 			check_quotes(t_str_pos *lexer);
int 			quotes_error(t_str_pos *lexer);
t_token 		*add_quoted_word(t_token_list *list, t_str_pos *lexer);
t_token 		*add_unquoted_word(t_token_list *list, t_str_pos *lexer);


#endif