/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:42:08 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/15 17:40:22 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_subs(char *raw)
{
	while (*raw)
	{
		if (*raw == '{' && *(raw + 1) == '{')
			return (true);
		raw++;
	}
	return (false);
}

void	init_exp(t_expand_type *exp, char *raw)
{
	exp->len_var = 0;
	exp->len_raw = ft_strlen(raw);
	exp->i = 0;
	exp->j = 0;
	exp->res = ft_calloc(exp->len_raw + 1, sizeof(char));
	if (!exp->res)
		return ;//what we need to free ?
	exp->var = NULL;
	exp->str = NULL;
}

bool	is_valid_var(char *var)
{
	if (ft_isalpha(*var) || *var == '_')
		return (true);
	return (false);
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
	new_ptr = malloc(new_size);
	if (!new_ptr)
	{
		if (ptr)
			free(ptr);
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

/* before changes
void	*my_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!ptr && new_size == 0)
		return (NULL);
	else if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	if (ptr)
	{
		if (old_size > new_size)
			memcpy(new_ptr, ptr, new_size);
		else
			memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}
	return(new_ptr);
} */