/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:12:26 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/02 14:53:40 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	handle_cd_error(int code, char *context)
{
	(void)code;
	ft_putstr_fd("minishell: cd : ", 2);
	ft_putendl_fd(context, 2);
	return (1);
}
