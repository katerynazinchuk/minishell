/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:51:59 by tchernia          #+#    #+#             */
/*   Updated: 2025/07/01 14:05:07 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_type	*get_node(const char *var, t_env_list *env_list)
{
	t_env_type	*cur;

	cur = env_list->head;
	while (cur)
	{
		if (ft_strcmp(var, cur->key) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

int	get_env_value(const char *var, t_env_list *env_list, char **result)
{
	t_env_type	*cur;

	cur = get_node(var, env_list);
	if (!cur || !cur->value)
		return (0);
	*result = cur->value;
	return (1);
}
