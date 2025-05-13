/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:45 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/12 15:08:19 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quotes_error(t_str_pos *lexer)
{
	printf("Error: No matching quotes found for token starting at index %d\n", lexer->start);
	return (0);
}
