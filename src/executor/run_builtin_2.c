/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:01:07 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/27 13:48:33 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv, t_env_list *env_list)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '=') != NULL)
			return (0);
		else
			unset_env(env_list, argv[i]);
		i++;
	}
	return (0);
}

int	builtin_env(char **argv, t_env_list *env_list)
{
	t_env_type	*current;

	if (argv[1])
		return (check_error(ENV_ERR, argv[1], GENERAL));
	current = env_list->head;
	while (current)
	{
		if (current->key && current->value)
		{
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(current->value, 1);
		}
		current = current->next;
	}
	return (0);
}

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
			ft_putstr_fd("numeric argument required\n", 2);
			exit(2);
		}
	}
	exit (0);
}
