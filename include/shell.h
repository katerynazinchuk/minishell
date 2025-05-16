/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:21:44 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/16 13:06:19 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

// #include "minishell.h"

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

#endif

// "huh huoh $USER $PWD $PWD $USER $786 $&*_ bigbgo" "1684 $78976 $UYU $USER $PWD $PWD"
// Token: [type = 0] [value = huh huoh $USER $PWD $PWD $USER $786 $&*_ bigbgo] [expanded = huh huoh tchernia /home/tchernia/Downloads/4_Minishell /home/tchernia/Downloads/4_Minishell tchernia 86  bigbgo][quotes = 2]
// Token: [type = 0] [value = 1684 $78976 $UYU $USER $PWD $PWD] [expanded = (null)][quotes = 2]



//
// Token: [type = 0] [value = 1644] [expanded = 1644][quotes = 0]
// command: 1644

// minishell> "1644 $16468"
// Token: [type = 0] [value = 1644 $16468] [expanded = 1644 6468][quotes = 2]
// command: "1644 $16468"

// minishell> "1644 $16468 $bniuh"
// Token: [type = 0] [value = 1644 $16468 $bniuh] [expanded = (null)][quotes = 2]
// command: "1644 $16468 $bniuh"