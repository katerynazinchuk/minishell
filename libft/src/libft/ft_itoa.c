/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:30:20 by tchernia          #+#    #+#             */
/*   Updated: 2024/10/22 18:38:00 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_intlen(int n);

char	*ft_itoa(int n)
{
	char	*int_str;
	long	num;
	size_t	int_len;

	int_len = ft_intlen(n);
	num = (long)n;
	int_str = (char *)malloc(sizeof(char) * (int_len + 1));
	if (!int_str)
		return (NULL);
	if (num < 0)
		num = -num;
	int_str[int_len] = '\0';
	while (int_len--)
	{
		int_str[int_len] = (num % 10) + '0';
		num = num / 10;
	}
	if (n < 0)
		int_str[0] = '-';
	return (int_str);
}

static size_t	ft_intlen(int n)
{
	size_t	counter;

	counter = 0;
	if (n <= 0)
		counter = 1;
	while (n)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}
