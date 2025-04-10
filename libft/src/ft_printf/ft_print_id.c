/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:06:24 by tchernia          #+#    #+#             */
/*   Updated: 2024/11/05 12:55:52 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_print_id(int num)
{
	size_t	numlen;
	long	n;

	n = (long)num;
	numlen = 0;
	if (n < 0)
	{
		ft_print_c('-');
		n = -n;
		numlen++;
	}
	if (n >= 10)
		numlen += ft_print_id(n / 10);
	n = n % 10 + '0';
	numlen += ft_print_c(n);
	return (numlen);
}
