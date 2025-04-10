/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:44:22 by tchernia          #+#    #+#             */
/*   Updated: 2024/10/21 16:31:34 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*new_dest;
	const unsigned char	*new_src;

	new_dest = (unsigned char *)dest;
	new_src = (const unsigned char *)src;
	if (n == 0 || new_dest == new_src)
		return (dest);
	if (new_src < new_dest)
	{
		new_dest += n -1;
		new_src += n -1;
		while (n--)
		{
			*new_dest = *new_src;
			new_dest--;
			new_src--;
		}
	}
	else
		ft_memcpy(new_dest, new_src, n);
	return (dest);
}
