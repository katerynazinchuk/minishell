/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Amirre <Amirre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:28:19 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/13 00:37:07 by Amirre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

#include "minishell.h"

//typedef int (*t_error_fn)(int errno, char *context, int exit_status, int should_return);
typedef int (*t_error_fn)(int errno, char *context, char *detail);

typedef struct s_error
{
    int	        code;
    t_error_fn	fn;
}   t_error;

//add enum for error types
//200-249 syntax
//250-300 execute

bool check_unmached_quotes(char *line);
bool last_pipe_error(char *line);
bool first_pipe_error(char *line);
char *join_input(char *line);
char *check_input(char *line);

/* _______________________________ */
int	commant_not_found(int code, char *context);
int	bad_subs(int code, char *context);
int	syntax_error(int code, char *context);


#endif