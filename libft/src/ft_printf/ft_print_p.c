/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:32:24 by tchernia          #+#    #+#             */
/*   Updated: 2024/11/07 15:07:52 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_print_p(uintptr_t p)
{
	const char	*base;
	ssize_t		plen;

	if (p == 0)
		return (write(1, "(nil)", 5));
	base = "0123456789abcdef";
	plen = 0;
	if (p < 16)
	{
		ft_print_str("0x");
		ft_print_c(base[p % 16]);
		return (3);
	}
	plen = ft_print_p(p / 16);
	plen += ft_print_c(base[p % 16]);
	return (plen);
}
