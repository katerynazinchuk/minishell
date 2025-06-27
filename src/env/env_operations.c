/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:59:49 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/27 13:59:07 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_list	*init_env_list(void);
static char			*error_and_free_node(t_env_type	*node, int need_free);

t_env_list	*fill_env_list(char **env)
{
	size_t		i;
	t_env_list	*env_list;
	t_env_type	*node;

	env_list = init_env_list();
	if (!env_list)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		node = fill_env_node(env[i]);
		if (!node)
		{
			free_env_list(env_list);
			return (NULL);
		}
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
	{
		check_error(ENOMEM, "create env list", GENERAL);
		return (NULL);
	}
	env_list->head = NULL;
	env_list->tail = NULL;
	env_list->size = 0;
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
	env_list->size++;
}

t_env_type	*fill_env_node(char *str)
{
	t_env_type	*node;
	int			j;

	j = 0;
	while (str[j] != '=')
		j++;
	node = (t_env_type *)malloc(sizeof(t_env_type));
	if (!node)
		error_and_free_node(node, 0);
	node->key = ft_substr(str, 0, j);
	if (!node->key)
		error_and_free_node(node, 1);
	node->value = ft_substr(str, j + 1, ft_strlen(str) - j - 1);
	if (!node->value)
		error_and_free_node(node, 1);
	node->next = NULL;
	return (node);
}

static char	*error_and_free_node(t_env_type *node, int need_free)
{
	check_error(ENOMEM, "create env node", GENERAL);
	if (need_free)
		free_env_node(node);
	return (NULL);
}
