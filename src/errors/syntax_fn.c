/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_fn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:23:30 by Amirre            #+#    #+#             */
/*   Updated: 2025/06/19 21:10:30 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_syntax_error(int code, char *context)
{
	(void)code;
	ft_putstr_fd("minishel: syntax error: ", 2);
	if (context)
		ft_putstr_fd(context, 2);
	return (1);
}
int	handle_token_error(int code, char *context)
{
	(void)code;
	ft_putstr_fd("minishel: syntax error ", 2);
	ft_putstr_fd(context, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	handle_bad_subs(int code, char *context)
{
	(void)code;
	(void)context;
	ft_putstr_fd("minishel: bad substitution\n", 2);
	return (1);
}
