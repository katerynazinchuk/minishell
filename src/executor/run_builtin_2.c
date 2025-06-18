/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:01:07 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/16 17:34:42 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_unset(char **argv, t_env_list *env_list)
{
	int i;
	int status;

	i = 1;
	status = 0;
	while(argv[i])
	{
		if (ft_strchr(argv[i], '=') != NULL)
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
			unset_env(env_list, argv[i]);
		i++;
	}
	return (status);
}
int		builtin_env(char **argv, t_env_list *env_list)
{
	t_env_type	*current;
	
	if (argv[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	current = env_list->head;
	while (current)
	{
		if (current->key && current->value)
		{
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(current->value, 1);
			write(1, "\n", 1);
		}
		current = current->next;
	}
	return (0);
}

int		builtin_exit(char **argv, t_env_list *env_list)
{
	(void)argv;
	(void)env_list;

	ft_putendl_fd("exit", 1);
	if(argv[1])
	{
		if (is_numeric(argv[1]))
		{
			if (argv[2])
			{
				ft_putstr_fd("exit: too many arguments\n", 2);
				return (1);
			}
			exit(ft_atoi(argv[1]));
		}
		else
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
	exit (0);
}
