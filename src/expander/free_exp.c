/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:16:23 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/16 13:32:53 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exp(t_expand_type *exp)
{
	if (exp->var)
	{
		free(exp->var);
		exp->var = NULL;
	}
	if (exp->str)
	{
		free(exp->str);
		exp->str = NULL;
	}
}

char	*error_free(t_expand_type *exp)
{
	free_exp(exp);//be sure in syntax
	if (exp->res)
	{
		free(exp->res);
		exp->res = NULL;
	}
	return (NULL);
}
