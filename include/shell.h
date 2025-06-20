/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:21:44 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/19 19:33:25 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "parser.h"

typedef struct s_shell
{
	t_env_list		*env_list;
	int				fd[2];
	int				status;
}	t_shell;

typedef struct s_session
{
	t_shell			*shell;
	t_token_list	*tokens;
	t_ast_node		*ast;
	char			*line;
	char			*prompt;
	int 			heredoc_count;
}	t_session;

void	init_shell(t_shell *shell, char **env);
void	run_shell(t_shell *shell);
int		shell_loop(t_session *session);
void	init_session(t_session *session, t_shell *shell);
int		process_line(t_session *session);
int		parser(t_session *session);
int		update_prompt(char **prompt);
int		shell_exit(t_session *session);
void	free_for_fork(t_session *session);

/* debug */
void	print_shell(t_shell *shell);
void	print_env_list(t_env_list *env_list);

#endif
