/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:05:54 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/01 12:23:20 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **argv, t_env_list *env_list)
{
	int		new_line;

	(void)env_list;
	argv++;
	new_line = 1;
	while (*argv && is_new_line(*argv))
	{
		new_line = 0;
		argv++;
	}
	while (*argv)
	{
		ft_putstr_fd(*argv, 1);
		if (*(argv + 1))
			write(1, " ", 1);
		argv++;
	}
	if (new_line)
		write(1, "\n", 1);
	return (0);
}
