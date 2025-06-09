/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:51:59 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/09 15:01:06 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_value(const char *var, t_env_list *env_list, char **result)
{
	t_env_type	*cur;

	cur = env_list->head;
	while(cur)
	{
		if (ft_strcmp(var, cur->key) == 0)
		{
			*result = ft_strdup(cur->value);
			if (!*result)
				return (2);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}
