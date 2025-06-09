/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:50:19 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/09 15:52:19 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

#define O_TMPFILE 020000000 | O_DIRECTORY

void heredoc_foreach_ast(t_ast_node *node, t_session *ctx ,void (*func)(t_redir *, t_session *));
void heredoc(t_ast_node *node, t_session *session);
void expand_heredoc(t_redir *redir, t_session *session);
void cleanup_heredoc(t_redir *redir, t_session *session);

#endif