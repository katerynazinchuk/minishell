/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:51:59 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/30 14:41:39 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_env_value(const char *var, t_env_list *env_list, char **result)
{
	t_env_type	*cur;

	cur = env_list->head;
	while(cur)
	{
		if (ft_strcmp(var, cur->key) == 0)
		{
			*result = ft_strdup(cur->value);
			if (!*result)
				return (false);
			return (true);
		}
		cur = cur->next;
	}
	return (false);
}
