/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_errors_frees.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:20:09 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/25 17:06:42 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_env_list *env_list)
{
	t_env_type	*current;
	t_env_type	*next;

	if (!env_list)
		return ;
	current = env_list->head;
	while (current)
	{
		next = current->next;
		free_env_node(current);
		current = next;
	}
	free(env_list);
}

void	free_env_node(t_env_type *node)
{
	if (node)
	{
		if (node->key)
			free(node->key);
		if (node->value)
			free(node->value);
		free(node);
	}
}
