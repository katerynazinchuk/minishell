/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:50:19 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/12 13:19:15 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

// typedef enum e_status
// {
// 	SUCCESS = 0,
// 	FAILURE,
// 	CRITICAL_ERROR,
// }	t_status;

// typedef struct s_res
// {
// 	t_status	status;
// 	const char 		*msg;
// }	t_res;

// t_res response(t_status status , const char *msg){
// 	t_res res;
// 	res.status = status;
// 	res.msg = msg;
// 	return (res);
// }

// return (response(FAILURE, "Meooooow!"));

// int is_success(t_res res)
// {
// 	return (res.status == SUCCESS);
// }



// #define O_TMPFILE 020000000 | O_DIRECTORY

void heredoc_foreach_ast(t_ast_node *node, t_session *ctx ,void (*func)(t_redir *, t_session *));
void heredoc(t_ast_node *node, t_session *session);
void expand_heredoc(t_redir *redir, t_session *session);
void cleanup_heredoc(t_redir *redir, t_session *session);

int event_handler(void);

#endif