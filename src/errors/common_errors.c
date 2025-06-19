/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:30:08 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/19 19:16:54 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_error(int *status)
{
	*status = 1;
	ft_putendl_fd("minishell: cannot allocate memory", 2);
}
