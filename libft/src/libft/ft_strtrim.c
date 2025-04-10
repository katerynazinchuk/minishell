/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:01:10 by tchernia          #+#    #+#             */
/*   Updated: 2024/10/22 18:29:50 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	left;
	size_t	right;

	left = 0;
	right = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[left]))
		left++;
	while (ft_strchr(set, s1[right]))
		right--;
	return (ft_substr(s1, left, right - left + 1));
}
