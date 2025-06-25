/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:51:26 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/25 16:53:13 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_tok_type
{
	T_WORD,
	T_PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HEREDOC,
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
	char				*expanded;
	int					bad_subs;
	t_tok_type			type;
	t_quoted			quoted;
	struct s_segment	*segment;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_segment
{
	char				*value;
	t_q_type			q_type;
	struct s_segment	*next;
}	t_segment;

typedef struct s_token_list
{
	int			error;
	t_token		*head;
	t_token		*tail;
}	t_token_list;

#endif