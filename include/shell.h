/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:21:44 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/24 18:03:27 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "parser.h"

typedef struct s_shell
{
	t_env_list		*env_list;
	t_token_list	*tokens;
	t_ast_node			*ast;
	char			*line;
	int				last_exit_status;
	char			*prompt;
}	t_shell;

void	init_shell(t_shell *shell, char **env);
void	run_shell(t_shell *shell);
bool	process_line(t_shell *shell);
// void	free_shell(t_shell *shell);
void	cleanup_cycle(t_shell *shell);

/* debug */
void	print_shell(t_shell *shell);
void	print_env_list(t_env_list *env_list);

#endif
