/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:50:19 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/26 19:01:55 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

void	heredoc_ast(t_ast_node *node, t_session *ctx);
void	heredoc(t_ast_node *node, t_session *session);
void	expand_heredoc(t_redir *redir, t_session *session);
int		handle_heredoc_sig(t_session *session, char *line);
char	*process_expansion(char *line, t_session *session);
int		write_heredoc_lines(t_redir *redir, t_session *session, int fd);
int		event_handler(void);

#endif