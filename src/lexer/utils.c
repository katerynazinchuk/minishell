/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:49:11 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/04/29 16:07:14 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char *ft_strndup(const char *s, size_t n)
{
    char    *new_str;
    size_t  i;

    new_str = (char *)malloc(sizeof(char) * (n + 1));
    if (!new_str)
        return (NULL);
    i = 0;
    while (i < n && s[i])
    {
        new_str[i] = s[i];
        i++;
    }
    new_str[i] = '\0';
    return (new_str);
}