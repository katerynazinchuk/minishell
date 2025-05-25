/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:21:44 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/25 16:46:16 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "parser.h"

typedef struct s_shell
{
	t_env_list		*env_list;
	int				last_exit_status;
}	t_shell;

typedef struct s_session
{
	t_shell			*shell;
	t_token_list	*tokens;
	t_ast_node		*ast;
	char			*line;
	char			*prompt;
}	t_session;

void	init_shell(t_shell *shell, char **env);
void	run_shell(t_shell *shell);
void	init_session(t_session *session, t_shell *shell);
bool	process_line(t_session *session);
bool	parser(t_session *session);

// void	free_shell(t_shell *shell);
void	cleanup_cycle(t_session *session);

/* debug */
void	print_shell(t_shell *shell);
void	print_env_list(t_env_list *env_list);

#endif
