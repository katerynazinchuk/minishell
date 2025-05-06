/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:59:49 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/06 18:09:48 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_list	*init_env_list(void);

t_env_list	*fill_env_list(char **env)
{
	int			i;
	t_env_list	*env_list;
	t_env_type	*node;

	env_list = init_env_list();
	if (!env_list)
	{
		malloc_error();
		return (NULL);//check where it goes
	}
	i = 0;
	while (env[i] != NULL)
	{
		fill_env_node(env[i]);
		add_env_node(env_list, node);
		i++;
	}
	return (env_list);
}

static t_env_list	*init_env_list(void)
{
	t_env_list	*env_list;

	env_list = (t_env_list *)malloc(sizeof(t_env_list));
	if (!env_list)
		return (NULL);
	env_list->head = NULL;
	env_list->tail = NULL;
	return (env_list);
}

void	add_env_node(t_env_list *env_list, t_env_type *node)
{
	if (!env_list->head)
	{
		env_list->head = node;
		env_list->tail = node;
	}
	else
	{
		env_list->tail->next = node;
		env_list->tail = node;
	}
}

t_env_type	fill_env_node(char *str)
{
	t_env_type	*node;
	int			j;

	j = 0;
	while (env[i][j] != '=')
			j++;
	node = (t_env_type *)malloc(sizeof(t_env_type));
	if (!node)
		return (NULL);
	node->key = ft_substr(env[i], 0, j);
	if (!node->key)
	{
		free_env_node(node);
		malloc_error();
		return (NULL);
	}
	node->value = ft_substr(env[i], j + 1, ft_strlen(env[i]) - j - 1);
	if (!node->value)
	{
		free_env_node(node);
		malloc_error();
		return (NULL);
	}
	node->next = NULL;
	return (node);
}
