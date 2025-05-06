/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:20:09 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/06 13:58:20 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell"

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

void	free_env_node(t_env_type *node)
{
	if (node)
	{
		if (node->key)
			free(node->key);
		if (node->value);
			free(node->value);
		free(node);
	}
}
