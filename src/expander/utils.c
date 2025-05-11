/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:42:08 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/11 16:18:25 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}
void	init_exp(t_expand_type *exp, char *raw)
{
	exp->len = 0;
	exp->i = 0;
	exp->j = 0;
	exp->res = ft_calloc(ft_strlen(raw) + 1, sizeof(char));
	if (!exp->res)
		return (NULL)//what we need to free ?
	exp->var = NULL;
	exp->expanded = NULL;
}

bool	is_valid_var(char *var)
{
	if (ft_isalpha(*var) || *var == '_')
		return (true);
	return (false);
}

/* //echo $? shows 0-255 with overflow
char	exit_status_to_char(int n)
{
	char str[4];

	while (n >= 0)
	{
		
	}
} */
