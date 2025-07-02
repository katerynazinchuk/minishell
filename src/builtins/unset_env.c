/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:01:07 by tchernia          #+#    #+#             */
/*   Updated: 2025/07/01 12:23:28 by kzinchuk         ###   ########.fr       */
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
