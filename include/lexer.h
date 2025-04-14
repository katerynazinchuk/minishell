/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:52:33 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/04/14 14:56:08 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"
# include "my_signal.h"

typedef enum e_token_type
{
	TOKEN_WORD,//argc, argv
	TOKEN_PIPE,//|
	TOKEN_REDIRECT_IN,//<
	TOKEN_REDIRECT_OUT,//>
	TOKEN_APPEND,//>>
	TOKEN_HEREDOC,//<<
	TOKEN_SPACE,
	TOKEN_EOF,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

//helps you avoid writing token_last() every time you want to add to the end.
typedef struct s_lexer_list
{
	t_token		*head;
	t_token		*tail;
}	t_lexer_list;

//help track the current position in the string, if we have multiple tokens
typedef struct s_lexer
{
	char	*input;
	int		current_index;
	int		start_index;//beggining of the token
	int		len;
}	t_lexer;

//Tracks whether you're inside single quotes, double quotes, or escaping a character (\)
typedef struct s_lexer_state
{
	int	quote;
	int	dquote;
	int	escape;
}	t_lexer_state;

#endif

//how to use later in tokenization
//token = extract_token(lexer, state);