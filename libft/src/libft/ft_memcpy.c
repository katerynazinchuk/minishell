/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:55:13 by tchernia          #+#    #+#             */
/*   Updated: 2024/10/21 16:30:44 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*new_dest;
	const unsigned char	*new_src;

	if (n == 0 || dest == src)
		return (dest);
	new_dest = (unsigned char *)dest;
	new_src = (const unsigned char *)src;
	while (n--)
	{
		*new_dest++ = *new_src++;
	}
	return (dest);
}
