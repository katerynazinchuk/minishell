/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:51:59 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/12 16:17:41 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Be carefull: there is malloc */
// int	get_env_value(const char *var, t_env_list *env_list, char **result)
// {
// 	t_env_type	*cur;

// 	cur = env_list->head;
// 	while(cur)
// 	{
// 		if (ft_strcmp(var, cur->key) == 0)
// 		{
// 			*result = cur->value;
// 			return (1);//success
// 		}
// 		cur = cur->next;
// 	}
// 	return (0);//variable not found
// }


/* Be carefull: there is malloc */
static t_env_type	*get_node(const char *var, t_env_list *env_list)
{
	t_env_type	*cur;

	cur = env_list->head;
	while(cur)
	{
		if (ft_strcmp(var, cur->key) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}


/* Be carefull: there is malloc */
int	get_env_value(const char *var, t_env_list *env_list, char **result)
{
	t_env_type	*cur;

	cur = get_node(var, env_list);
	if (!cur)
		return (0);
	*result = cur->value;
	return (1);
}

int	update_env_list(const char *var, t_env_list *env_list, char *new_data)
{
	t_env_type	*cur;

	cur = get_node(var, env_list);
	free(cur->value);
	cur->value = ft_strdup(new_data);
	if (!cur->value)
		return (ENOMEM);
	return (0);//success
}