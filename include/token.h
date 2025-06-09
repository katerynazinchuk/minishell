/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:51:26 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/09 15:36:39 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_tok_type
{
	T_WORD,
	T_PIPE,
	T_IN,//<
	T_OUT,//>
	T_APPEND,//>>
	T_HEREDOC,//<<
	T_EOF,
}	t_tok_type;

typedef enum e_q_type
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE,
}	t_q_type;

typedef enum e_quoted
{
	UNQUOTED,
	QUOTED,
}	t_quoted;

typedef struct s_token
{
	char			*expanded;
	int				bad_subs;
	t_tok_type		type;
	t_quoted		quoted; // to track if the token is quoted for heredoc expansion
	struct s_segment	*segment;
	struct s_token	*next;
	struct s_token	*prev; // to track the last token for heredoc
}	t_token;

typedef struct s_segment
{
	char				*value;
	t_q_type			q_type;
	struct s_segment	*next;
}	t_segment;

//if any of the segments is quoted, the whole token is considered quoted - logic for heredoc var expansion
//expand heredoc content only if unquoted

typedef struct s_token_list
{
	int 		error;// to track errors (not sure yet)
	t_token		*head;
	t_token		*tail;
}	t_token_list;

#endif