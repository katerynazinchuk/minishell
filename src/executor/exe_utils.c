/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:07:56 by tchernia          #+#    #+#             */
/*   Updated: 2025/07/03 18:07:10 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_env_array(char **env_arr, t_env_type *current);

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

static size_t	count_env(t_env_list *env_list)
{
	t_env_type	*head;
	int			count;

	count = 0;
	head = env_list->head;
	while (head)
	{
		if (head->value != NULL)
			count++;
		head = head->next;
	}
	return (count);
}

char	**env_to_arr(t_env_list *env_list)
{
	char		**env_arr;

	env_arr = (char **)ft_calloc(sizeof(char *), count_env(env_list) + 1);
	if (!env_arr)
	{
		check_error(ENOMEM, "executor", GENERAL);
		return (NULL);
	}
	if (fill_env_array(env_arr, env_list->head))
		return (NULL);
	return (env_arr);
}

static int	fill_env_array(char **env_arr, t_env_type *current)
{
	size_t	i;

	i = 0;
	while (current)
	{
		if (current->value)
		{
			env_arr[i] = to_str(current);
			if (!env_arr[i])
			{
				env_arr[i] = NULL;
				free_arr(env_arr);
				return (1);
			}
			i++;
		}
		current = current->next;
	}
	return (0);
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
