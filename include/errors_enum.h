/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_enum.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:19:33 by Amirre            #+#    #+#             */
/*   Updated: 2025/06/25 18:47:39 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_ENUM_H
# define ERRORS_ENUM_H

typedef enum s_error_code
{
	SYNTAX_ERR = 200,
	TOKEN_ERR,
	BAD_SUBS,
	EXECUTE_ERR = 250,
	REDIRECT_FAIL,
	CMD_NOT_FOUND,
	CD_ERR,
	IS_DIR
	
}	t_error_code;

#endif