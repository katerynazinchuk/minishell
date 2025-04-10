/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:39:26 by tchernia          #+#    #+#             */
/*   Updated: 2024/11/05 12:58:30 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_print_u(unsigned int num)
{
	ssize_t	numlen;

	numlen = 0;
	if (num >= 10)
		numlen += ft_print_u(num / 10);
	num = num % 10 + '0';
	numlen += ft_print_c(num);
	return (numlen);
}
