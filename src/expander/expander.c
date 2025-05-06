/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:59:49 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/06 13:04:14 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_list	*init_env_list(void);

t_env_list	*fill_env_list(char **env)
{
	int			i;
	int			j;
	t_env_list	*env_list;
	t_env_type	*node;

	env_list = init_env_list();
	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		node = (t_env_type *)malloc(sizeof(t_env_type));
		if (!node)
		{
			free_env_list(env_list);
			return (malloc_error());
		}
		node->key = ft_substr(env[i], 0, j);
		if (!node->key)
		{
			free_env_list(env_list);
			malloc_error ();
			exit (1);
		}
		node->value = ft_substr(env[i], j + 1, ft_strlen(env[i]) - j - 1);
		if (!node->key)
		{
			free_env_list(env_list);
			malloc_error ();
			exit (1);
		}
		node->next = NULL;
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

void	free_env_list(t_env_list *env_list)
{
	t_env_type	*current;
	t_env_type	*next;

	if (!env_list)
		return ();
	current = env_list->head;
	while (current)
	{
		next = current->next;
		if (current->key != NULL)
			free(current->key);
		if (current->value != NULL)
			free(current->value);
		free(current);
		current = next;
	}
	free(env_list);
}

void	malloc_error(void)
{
	const char *str = "Cannot allocate memory";
	ft_putendl_fd(str, stderr);
}
