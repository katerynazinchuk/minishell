/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:20:35 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/26 15:39:07 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void append_segment(t_segment **head, t_segment *new_seg)
{
	t_segment *current;

	if(!*head)
	{
		*head = new_seg;
		return;
	}
	current = *head;
	while(current->next)
		current = current->next;
	current->next = new_seg;
}