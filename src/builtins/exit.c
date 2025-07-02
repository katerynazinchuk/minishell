/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:06:12 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/02 13:42:35 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *str);

int	builtin_exit(char **argv, t_env_list *env_list)
{
	(void)argv;
	(void)env_list;
	ft_putendl_fd("exit", 1);
	if (argv[1])
	{
		if (is_numeric(argv[1]))
		{
			if (argv[2])
			{
				ft_putstr_fd("minshell: exit: too many arguments\n", 2);
				return (1);
			}
			exit(ft_atoi(argv[1]));
		}
		else
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(2);
		}
	}
	exit (0);
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
