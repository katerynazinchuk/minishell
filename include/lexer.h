/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:52:33 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/04/14 15:56:15 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"
# include "my_signal.h"
# include "token.h"

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