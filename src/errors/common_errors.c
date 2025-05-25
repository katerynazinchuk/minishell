/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:30:08 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/25 13:06:32 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_error(int *last_exit_status)
{
	*last_exit_status = 1;
	ft_putendl_fd("minishell: cannot allocate memory", 2);
}
