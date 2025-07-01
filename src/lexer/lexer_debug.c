/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:51:46 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/01 12:14:59 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_segments(t_segment *segment)
{
	t_segment	*current;

	if (!segment)
		return ;
	current = segment;
	while (current)
	{
		printf("%s ", current->value);
		current = current->next;
	}
}

// void	print_tokens(t_token_list *list)
// {
// 	t_token	*current;
// 	char	*map[7] = {"T_WORD", "T_PIPE", "T_IN", \
// "T_OUT", "T_APPEND", "T_HEREDOC", "T_EOF"};

// 	if (!list || !list->head)
// 	{
// 		printf("No tokens to print.\n");
// 		return ;
// 	}
// 	current = list->head;
// 	while (current)
// 	{
// 		printf("[%s] %s\n  ", map[current->type], current->expanded);
// 		print_segments(current->segment);
// 		printf("\n");
// 		current = current->next;
// 	}
// }
