/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:51:26 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/12 15:17:19 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	TOKEN_WORD,//argc, argv
	TOKEN_PIPE,//|
	TOKEN_REDIRECT_IN,//<
	TOKEN_REDIRECT_OUT,//>
	TOKEN_APPEND,//>>
	TOKEN_HEREDOC,//<<
}	t_token_type;

//Tracks whether you're inside single quotes, double quotes
typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
}	t_quote_type;

typedef struct s_token
{
	char			*value;
	int				bad_subs;
	t_token_type	type;
	t_quote_type	t_quote_type;
	struct s_token	*next;
}	t_token;

//helps you avoid writing token_last() every time you want to add to the end.
typedef struct s_token_list
{
	int 	error;// to track errors (not sure yet)
	t_token		*head;
	t_token		*tail;
}	t_token_list;

#endif