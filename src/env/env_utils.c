/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:51:59 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/08 11:59:16 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(const char *var, t_env_list *env_list)
{
	t_env_type	*cur;

	cur = env_list->head;
	while(cur)
	{
		if (ft_strcmp(var, cur->key) == 0)
		{
			return (cur->value);
		}
		cur = cur->next;
	}
	return (NULL);
}

/* 
bool	get_env_value_const(const char *var, t_env_list *env_list, const char **result)
{
	t_env_type	*cur;

	cur = env_list->head;
	while(cur)
	{
		if (ft_strcmp(var, cur->key) == 0)
		{
			*result = (const char *cur->value);
			if (!*result)
				return (false);
			return (true);
		}
		cur = cur->next;
	}
	return (false);
} */