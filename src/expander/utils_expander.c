/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:42:08 by tchernia          #+#    #+#             */
/*   Updated: 2025/07/05 14:08:53 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_subs(char *raw)
{
	while (*raw)
	{
		if (*raw == '{' && ft_strchr(raw + 1, '{') != 0)
			return (true);
		raw++;
	}
	return (false);
}

int	init_exp(t_expand_type *exp, char *raw)
{
	exp->len_var = 0;
	exp->len_raw = ft_strlen(raw);
	exp->i = 0;
	exp->j = 0;
	exp->res = ft_calloc(exp->len_raw + 1, sizeof(char));
	if (!exp->res)
	{
		check_error(ENOMEM, NULL, GENERAL);
		return (1);
	}
	exp->var = NULL;
	exp->str = NULL;
	return (0);
}

int	check_expand_case(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	else if (c == '?')
		return (1);
	else if (ft_isdigit(c))
		return (1);
	return (0);
}

void	*my_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	new_ptr = ft_calloc(1, new_size);
	if (!new_ptr)
	{
		if (ptr)
			free(ptr);
		check_error(ENOMEM, "my_relloc fail", GENERAL);
		return (NULL);
	}
	if (ptr)
	{
		if (old_size > new_size)
			ft_memcpy(new_ptr, ptr, new_size);
		else
			ft_memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}
	return (new_ptr);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
