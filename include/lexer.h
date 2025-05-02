/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:52:33 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/02 13:30:01 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"
# include "my_signal.h"
# include "token.h"

//help track the current position in the string, if we have multiple tokens
typedef struct s_str_pos
{
	char	*input;
	int		start;//beginning of the token
	int		current;
	int		len;
}	t_str_pos;

//Tracks whether you're inside single quotes, double quotes


//functions
int		is_whitespace(char c);
char	*ft_strndup(const char *s, size_t n);

t_token *create_token(char *value, t_token_type types, t_quote_type quotes);
void	add_to_token_list(t_token_list *list, t_token *new_token);
void	free_token(t_token *token);
void	free_token_list(t_token_list *list);

void	init_lexer_state(t_str_pos *lexer, char *line);
t_token_list	*init_token_list(void);

void	skip_whitespace(t_str_pos *lexer);
void	add_pipe_token(t_token_list *list, t_str_pos *lexer);
void	add_redirection_token(t_token_list *list, t_str_pos *lexer);
void	add_word_token(t_token_list *list, t_str_pos *lexer);

t_token_list	*lexer(char *line);
void	print_tokens(t_token_list *list);

#endif

//how to use later in tokenization
//token = extract_token(lexer, state);