/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_enum.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:19:33 by Amirre            #+#    #+#             */
/*   Updated: 2025/06/20 16:32:40 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_ENUM_H
# define ERRORS_ENUM_H

typedef enum s_error_code
{
    SYNTAX_ERROR = 200,
    TOKEN_ERROR,
    BAD_SUBS,
    
    
    EXECUTE_ERROR = 250,
    REDIRECT_FAIL,
    CMD_NOT_FOUND,
    CD_ERR
}   t_error_code;


#endif