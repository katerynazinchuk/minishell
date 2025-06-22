/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:30:21 by Amirre            #+#    #+#             */
/*   Updated: 2025/06/22 17:22:29 by tchernia         ###   ########.fr       */
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
	ft_putstr_fd(": redirect fail\n", 2);
	return (1);
}

int	handle_cmd_not_found(int code, char *context)
{
	(void)code;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(context, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (127);
}
int	handle_cd_error(int code, char *context)
{
	(void)code;
	ft_putstr_fd("minishell: cd : ", 2);
	ft_putstr_fd(context, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	handle_is_dir(int code, char *context)
{
	(void)code;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(context, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	return (126);
}

//  cat -e Makefile > 1.txt | echo 1.txt | bkbl