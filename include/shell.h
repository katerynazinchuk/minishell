/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:21:44 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/17 12:20:50 by kzinchuk         ###   ########.fr       */
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
void	free_shell(t_shell	*shell);

#endif
