/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bultin_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:01:07 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/11 19:06:22 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_unset(char **argv, t_env_list *env_list)
{
	(void)argv;
	(void)env_list;
	return (0);
}
int		builtin_env(char **argv, t_env_list *env_list)
{
	(void)argv;
	(void)env_list;
	return (0);
}

int		builtin_exit(char **argv, t_env_list *env_list)
{
	(void)argv;
	(void)env_list;
	return (0);
}
