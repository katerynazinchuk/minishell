/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:51:59 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/23 19:52:27 by kzinchuk         ###   ########.fr       */
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
t_env_type	*get_node(const char *var, t_env_list *env_list)
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

int	get_env_value(const char *var, t_env_list *env_list, char **result)
{
	t_env_type	*cur;

	cur = get_node(var, env_list);
	if (!cur || !cur->value)
	{
		// write(1, "9\n", 2);
		return (0);
	*result = cur->value;
	return (1);
}

int	update_env_list(const char *var, t_env_list *env_list, char *new_data)
{
	t_env_type	*cur;

	if(!new_data)
		return (0);
	cur = get_node(var, env_list);
	if(!cur)
		return (ENOENT); //malloc error
	free(cur->value);
	cur->value = ft_strdup(new_data);
	if (!cur->value)
		return (ENOMEM);
	return (0);//success
}
int set_env(t_env_list *env_list, const char *var, const char *value)
{
	t_env_type	*node;

	node = get_node(var, env_list);
	if (node)
		return update_env_list(var, env_list, (char *)value);
	node = (t_env_type *)malloc(sizeof(t_env_type));
	if (!node)
		return (ENOMEM);
	node->key = ft_strdup(var);
	if (!node->key)
	{
		free(node);
		return (ENOMEM);
	}
	if(value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
		{
			free_env_node(node);
			return (ENOMEM);
		}
	}
	else
		node->value = NULL; // if value is NULL, we set it to NULL
	node->next = NULL;
	add_env_node(env_list, node);
	return (0); //success
}

void unset_env(t_env_list *env_list, const char *var)
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
