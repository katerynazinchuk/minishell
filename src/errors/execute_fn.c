/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:30:21 by Amirre            #+#    #+#             */
/*   Updated: 2025/07/01 13:51:20 by tchernia         ###   ########.fr       */
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

int	handle_cd_error(int code, char *context)
{
	(void)code;
	ft_putstr_fd("minishell: cd : ", 2);
	ft_putendl_fd(context, 2);
	return (1);
}

int	handle_is_dir(int code, char *context)
{
	(void)code;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(context, 2);
	ft_putendl_fd(": Is a directory", 2);
	return (126);
}

int	handle_export_err(int code, char *context)
{
	(void)code;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(context, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

int	handle_env_err(int code, char *context)
{
	(void)code;
	ft_putstr_fd("env: ‘", 2);
	ft_putstr_fd(context, 2);
	ft_putendl_fd("’: No such file or directory", 2);
	return (127);
}
