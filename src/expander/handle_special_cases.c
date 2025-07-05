/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special_cases.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:16:43 by tchernia          #+#    #+#             */
/*   Updated: 2025/07/05 12:28:58 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_double_dollar_sign(char *raw, t_expand_type *exp)
{
	while (raw[exp->i + 1] && raw[exp->i + 1] == '$')
		exp->res[exp->j++] = raw[exp->i++];
	exp->res[exp->j++] = raw[exp->i++];
}

void handle_forward_slash(char *raw, t_expand_type *exp)
{
	while (raw[exp->i + 1] &&  !is_whitespace(raw[exp->i + 1])
			&& raw[exp->i + 1] != '$')
		exp->res[exp->j++] = raw[exp->i++];
}
