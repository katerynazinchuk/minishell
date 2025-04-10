/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:46:58 by tchernia          #+#    #+#             */
/*   Updated: 2024/11/05 12:55:47 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_print_x(unsigned long hex, const char c)
{
	const char	*base;
	ssize_t		numlen;

	numlen = 0;
	if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (hex >= 16)
		numlen += ft_print_x(hex / 16, c);
	numlen += ft_print_c(base[hex % 16]);
	return (numlen);
}
