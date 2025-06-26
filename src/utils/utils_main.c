/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:25:07 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/26 19:27:09 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ignore_args(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

int	shell_exit(t_session *session)
{
	write(1, "exit\n", 5);
	free_for_fork(session);
	return (1);
}
