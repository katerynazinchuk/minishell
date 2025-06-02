/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:50:19 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/02 13:13:11 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

void heredoc_foreach_ast(t_ast_node *node, t_session *ctx ,void (*func)(t_redir *, t_session *));
void heredoc(t_ast_node *node, t_session *session);
void expand_heredoc(t_redir *redir, t_session *session);

#endif