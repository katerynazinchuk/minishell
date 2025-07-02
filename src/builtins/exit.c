/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:06:12 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/02 17:35:16 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *str);

int	builtin_exit(char **argv, t_env_list *env_list)
{
	(void)argv;
	env_list->is_run = 0;
	ft_putendl_fd("exit", 1);
	if (argv[1])
	{
		if (is_numeric(argv[1]))
		{
			if (argv[2])
			{
				env_list->is_run = 1;
				ft_putendl_fd("minshell: exit: too many arguments", 2);
				return (1);
			}
			return (ft_atoi(argv[1]));
		}
		else
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			return (2);
		}
	}
	return (0);
}

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
		if (!str[i])
			return (0);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
