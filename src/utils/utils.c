/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:32 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/30 14:30:10 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <stdlib.h>
// #include <unistd.h>

char *ft_strndup(const char *s, size_t n)
{
	char	*new_str;
	size_t		i;

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

int	is_whitespace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}
int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '"');
}
