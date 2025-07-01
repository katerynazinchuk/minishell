/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:51:59 by tchernia          #+#    #+#             */
/*   Updated: 2025/07/01 13:27:43 by tchernia         ###   ########.fr       */
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
//rewrite to update exactly node
int	update_env_list(const char *var, t_env_list *env_list, char *new_data)
{
	t_env_type	*cur;

	if (!new_data)
		return (1);
	cur = get_node(var, env_list);
	if (!cur)
		return (0);
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
		return (update_env_list(key, env_list, (char *)value));
	else
	{
		node = (t_env_type *)malloc(sizeof(t_env_type));
		if (!node)
			return (check_error(ENOMEM, NULL, GENERAL));
		node->key = ft_strdup(key);
		if (!node->key)
		{
			free(node);
			return (check_error(ENOMEM, NULL, GENERAL));
		}
		if (value)
		{
			node->value = ft_strdup(value);
			if (!node->value)
			{
				free_env_node(node);
				return (check_error(ENOMEM, NULL, GENERAL));
			}
		}
		else
			node->value = NULL;
		node->next = NULL;
		add_env_node(env_list, node);
		return (0);
	}
}

/* int	set_env(t_env_list *env_list, const char *key, const char *value)
{
	t_env_type	*node;

	node = get_node(key, env_list);
	if (node)
		return (update_env_list(key, env_list, (char *)value));
	node = (t_env_type *)malloc(sizeof(t_env_type));
	if (!node)
		return (check_error(ENOMEM, NULL, GENERAL));
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (check_error(ENOMEM, NULL, GENERAL));
	}
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
		{
			free_env_node(node);
			return (check_error(ENOMEM, NULL, GENERAL));
		}
	}
	else
		node->value = NULL;
	node->next = NULL;
	add_env_node(env_list, node);
	return (0);
} */

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
