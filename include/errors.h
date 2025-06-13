/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Amirre <Amirre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:28:19 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/13 13:33:50 by Amirre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

#include "minishell.h"

//typedef int (*t_error_fn)(int errno, char *context, int exit_status, int should_return);
typedef int (*t_error_fn)(int code, char *context, char *msg);

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
int	cmd_not_found(int code, char *context, char *msg);
int	bad_subs(int code, char *context, char *msg);
int	syntax_error(int code, char *context, char *msg);
int	execute_error(int code, char *context, char *msg);
int	redirect_fail(int code, char *context, char *msg);

#endif