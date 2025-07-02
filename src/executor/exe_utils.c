/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:07:56 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/26 13:35:14 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*to_str(t_env_type *cur)
{
	size_t	len;
	char	*str;

	len = ft_strlen(cur->key) + ft_strlen(cur->value) + 1;
	str = ft_calloc(sizeof(char), len + 1);
	if (!str)
	{
		check_error(ENOMEM, "executor", GENERAL);
		return (NULL);
	}
	ft_strlcat(str, cur->key, len + 1);
	ft_strlcat(str, "=", len + 1);
	ft_strlcat(str, cur->value, len + 1);
	return (str);
}

char	**env_to_arr(t_env_list *env_list)
{
	char		**env_arr;
	t_env_type	*current;
	size_t		i;

	env_arr = (char **)ft_calloc(sizeof(char *), env_list->size + 1);
	if (!env_arr)
	{
		check_error(ENOMEM, "executor", GENERAL);
		return (NULL);
	}
	current = env_list->head;
	i = 0;
	while (current)
	{
		env_arr[i] = to_str(current);
		if (!env_arr[i])
		{
			env_arr[i] = NULL;
			free_arr(env_arr);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	return (env_arr);
}

bool	is_new_line(char *str)
{
	if (!str || str[0] != '-')
		return (false);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (false);
		str++;
	}
	return (true);
}
