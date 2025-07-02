/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:30:21 by Amirre            #+#    #+#             */
/*   Updated: 2025/07/02 14:13:04 by kzinchuk         ###   ########.fr       */
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
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(": redirect fail", 2);
	return (1);
}

int	handle_cmd_not_found(int code, char *context)
{
	(void)code;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(context, 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}

int	handle_is_dir(int code, char *context)
{
	(void)code;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(context, 2);
	ft_putendl_fd(": Is a directory", 2);
	return (126);
}
