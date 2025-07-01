/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:58:42 by tchernia          #+#    #+#             */
/*   Updated: 2025/07/01 12:23:24 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin_fn	get_builtin_fn(char *cmd)
{
	static const t_builtin	builtin[] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{NULL, NULL}
	};
	int						i;

	i = 0;
	while (builtin[i].name)
	{
		if (ft_strcmp(cmd, builtin[i].name) == 0)
			return (builtin[i].func);
		i++;
	}
	return (NULL);
}
