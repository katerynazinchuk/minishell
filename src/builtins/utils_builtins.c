/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:56:35 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/01 14:16:56 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env_node(t_env_type *node, char *new_data)
{
	if (!new_data)
		return (1);
	free(cur->value);
	cur->value = ft_strdup(new_data);
	if (!cur->value)
		return (check_error(ENOMEM, NULL, GENERAL));
	return (0);
}

int	set_env(t_env_list *env_list, const char *key, const char *value)
{
	t_env_type	*node;

	node = get_node(key, env_list);
	if (node)
		return (update_env_node(node, (char *)value));
	if (create_env_node(&node, key, value))
		return (1);
	add_env_node(env_list, node);
	return (0);
}

int	create_env_node(t_env_type **input, const char *key, const char *value)
{
	t_env_type	*node;

	node = (t_env_type *)malloc(sizeof(t_env_type));
	if (!node)
		return (check_error(ENOMEM, NULL, GENERAL), 1);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (check_error(ENOMEM, NULL, GENERAL), 1);
	}
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
		{
			free_env_node(node);
			return (check_error(ENOMEM, NULL, GENERAL), 1);
		}
	}
	else
		node->value = NULL;
	node->next = NULL;
	*input = node;
	return (0);
}

void	unset_env(t_env_list *env_list, const char *var)
{
	t_env_type	*cur;
	t_env_type	*prev;

	cur = env_list->head;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(var, cur->key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				env_list->head = cur->next;
			if (cur == env_list->tail)
				env_list->tail = prev;
			free_env_node(cur);
			env_list->size--;
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
