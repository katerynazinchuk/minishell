/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:30:21 by Amirre            #+#    #+#             */
/*   Updated: 2025/06/20 11:51:17 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_execute_error(int code, char *context)
{
	(void)code;
	(void)context;
	return (1);
}

int	handle_redirect_fail(int code, char *context)
{
	(void)code;
	(void)context;
	ft_putstr_fd(": command not found\n", 2);
	return (1);
}

int	handle_cmd_not_found(int code, char *context)
{
	(void)code;
	ft_putstr_fd(context, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (127);
}

//  cat -e Makefile > 1.txt | echo 1.txt | bkbl