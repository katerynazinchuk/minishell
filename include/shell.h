/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:21:44 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/06 16:49:06 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_shell
{
	t_env_list		*env_list;
	t_token_list	*token_list;
	//t_ast			*ast;
	char			*line;
	int				last_exit_status;
	char			*prompt;
}	t_shell_type;

