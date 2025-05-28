/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:51:26 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/28 17:59:51 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_tok_type
{
	T_WORD,//argc, argv
	T_PIPE,//|
	T_IN,//<
	T_OUT,//>
	T_APPEND,//>>
	T_HEREDOC,//<<
	T_SPACE,
}	t_tok_type;

//Tracks whether you're inside single quotes, double quotes
typedef enum e_q_type
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE,
}	t_q_type;

typedef struct s_token
{
	char			*expanded;
	int				bad_subs;
	t_tok_type		type;
	struct s_segment	*segment;
	struct s_token	*next;
}	t_token;

typedef struct s_segment
{
	char				*value;
	t_q_type			q_type;
	struct s_segment	*next;
}	t_segment;

//helps to avoid writing token_last() every time you want to add to the end.
typedef struct s_token_list
{
	int 		error;// to track errors (not sure yet)
	t_token		*head;
	t_token		*tail;
}	t_token_list;

#endif