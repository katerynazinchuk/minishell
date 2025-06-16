/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_fn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:23:30 by Amirre            #+#    #+#             */
/*   Updated: 2025/06/16 12:35:16 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_syntax_error(int code, char *context)
{
	(void)code;
	(void)context;
	return (1);
}

int	handle_bad_subs(int code, char *context)
{
	(void)code;
	(void)context;
	return (1);
}
