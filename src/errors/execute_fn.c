/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Amirre <Amirre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:23:30 by Amirre            #+#    #+#             */
/*   Updated: 2025/06/13 15:23:48 by Amirre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_not_found(int code, char *context, char *msg)
{
	
	return (1);
}

int	bad_subs(int code, char *context, char *msg)
{
	return (1);
}

int	syntax_error(int code, char *context, char *msg)
{
	return (1);
}
