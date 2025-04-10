/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:10:53 by tchernia          #+#    #+#             */
/*   Updated: 2024/11/08 12:04:09 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_print_str(char *str)
{
	size_t	len;

	if (str == NULL)
		return (write(1, "(null)", 6));
	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (write(1, str, len));
}
