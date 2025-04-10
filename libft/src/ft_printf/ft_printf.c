/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:54:12 by tchernia          #+#    #+#             */
/*   Updated: 2024/11/08 13:28:14 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static ssize_t	ft_check(const char *f, va_list *args);
static int		free_return(va_list args, int len);

int	ft_printf(const char *f, ...)
{
	size_t	len;
	ssize_t	count;
	va_list	args;

	if (!f)
		return (-1);
	va_start(args, f);
	len = 0;
	while (*f)
	{
		if (*f == '%' && *(f + 1) == '\0')
			return (free_return(args, -1));
		else if (*f == '%')
		{
			f++;
			count = ft_check(f, &args);
		}
		else
			count = write (1, f, 1);
		if (count == -1)
			return (free_return(args, -1));
		f++;
		len += count;
	}
	return (free_return(args, len));
}

static ssize_t	ft_check(const char *f, va_list *args)
{
	if (*f == '%')
		return (write (1, f, 1));
	else if (*f == 'c')
		return (ft_print_c((char)va_arg(*args, int)));
	else if (*f == 's')
		return (ft_print_str((char *)va_arg(*args, char *)));
	else if (*f == 'i' || *f == 'd')
		return (ft_print_id((int)va_arg(*args, int)));
	else if (*f == 'u')
		return (ft_print_u((unsigned int)va_arg(*args, unsigned int)));
	else if (*f == 'x' || *f == 'X')
		return (ft_print_x((unsigned int)va_arg(*args, unsigned int), *f));
	else if (*f == 'p')
		return (ft_print_p((uintptr_t)va_arg(*args, void *)));
	else
		return (write(1, (f - 1), 2));
	return (0);
}

static int	free_return(va_list args, int len)
{
	va_end(args);
	return (len);
}
