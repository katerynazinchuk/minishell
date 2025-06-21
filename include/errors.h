/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:28:19 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/21 16:44:32 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"
# include "shell.h"


//typedef int (*t_error_fn)(int errno, char *context, int exit_status, int should_return);
typedef int (*t_error_fn)(int code, char *context);

typedef struct s_error
{
	int	        code;
	t_error_fn	fn;
}   t_error;

//add enum for error types
//200-249 syntax
//250-300 execute

bool	check_unmached_quotes(char *line);
bool	last_pipe_error(char *line);
bool	first_pipe_error(char *line);
char	*join_input(char *line, int *flag, t_shell *shell);
int		check_input(char *line, t_session *session);


/* ________________________________ */
int	check_error(int err_code, char *context);


/* _______________________________ */
int	handle_cmd_not_found(int code, char *context);
int	handle_bad_subs(int code, char *context);
int	handle_syntax_error(int code, char *context);
int	handle_execute_error(int code, char *context);
int	handle_redirect_fail(int code, char *context);
int	handle_token_error(int code, char *context);
int	handle_cd_error(int code, char *context);


#endif