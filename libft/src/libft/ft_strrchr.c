/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:49:43 by tchernia          #+#    #+#             */
/*   Updated: 2024/10/22 16:05:33 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	chr;
	char			*last;

	chr = (unsigned char)c;
	last = NULL;
	while (*s != '\0')
	{
		if (*s == chr)
			last = (char *)s;
		s++;
	}
	if (chr == '\0')
		return ((char *)s);
	return ((char *)last);
}
