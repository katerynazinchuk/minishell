/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:21:44 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/16 14:18:01 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

typedef struct s_shell
{
	t_env_list		*env_list;
	t_token_list	*tokens;
	//t_ast			*ast;
	char			*line;
	int				last_exit_status;
	char			*prompt;
}	t_shell;

void	init_shell(t_shell *shell, char **env);
void	free_shell(t_shell	*shell);

#endif
