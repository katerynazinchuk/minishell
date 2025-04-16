/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:51:26 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/04/16 15:48:05 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "minishell.h"
# include "my_signal.h"
# include "lexer.h"

typedef enum token_type
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
typedef struct s_token_list
{
	t_token		*head;
	t_token		*tail;
}	t_token_list;

#endif