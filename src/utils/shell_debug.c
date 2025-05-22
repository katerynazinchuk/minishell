/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:57:30 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/22 13:10:13 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_list(t_env_list *env_list);

void	print_shell(t_shell *shell)
{
	if (shell->env_list)
		print_env_list(shell->env_list);
	// if (shell->tokens)
		
	// if (shell->line)
	

}

static void	print_env_list(t_env_list *env_list)
{
	t_env_type	*current;
	
	current = env_list->head;
	while (current)
	{
		printf("key: %s\n value: %s\n\n", current->key, current->value);
		current = current->next;
	}
}
