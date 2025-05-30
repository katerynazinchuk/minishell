/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:45 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/30 14:33:48 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quotes_error(t_str_pos *lexer)
{
	printf("Error: No matching quotes found for token starting at index %d\n", lexer->current);
	return (0);
}
