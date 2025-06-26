/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:16:23 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/26 13:41:35 by kzinchuk         ###   ########.fr       */
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

int	error_free(t_expand_type *exp)
{
	free_exp(exp);
	if (exp->res)
	{
		free(exp->res);
		exp->res = NULL;
	}
	return (1);
}
