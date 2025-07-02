/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_enum.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:19:33 by Amirre            #+#    #+#             */
/*   Updated: 2025/07/02 19:01:13 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_ENUM_H
# define ERRORS_ENUM_H

typedef enum s_error_code
{
	SYNTAX_ERR = 200,
	TOKEN_ERR,
	SUBS_ERR,
	EXECUTE_ERR = 250,
	REDIRECT_FAIL,
	CMD_NOT_FOUND,
	CD_ERR,
	IS_DIR,
	EXPORT_ERR,
	ENV_ERR
}	t_error_code;

#endif