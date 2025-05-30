/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:58:42 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/30 14:20:24 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin(t_cmd_info *cmd_info, t_shell *shell)
{
	static const t_builtin_entry	builtins[] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{NULL, NULL}
	};
	int								i;

	i = 0;
	while (builtins[i].name)
	{
		if(ft_strcmp(argv[0], builtins[i].name) == 0)
			return (builtins[i].func(argv, env_list));
		i++;
	}
	return(1);
}
