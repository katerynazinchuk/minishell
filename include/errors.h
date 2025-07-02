/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:28:19 by tchernia          #+#    #+#             */
/*   Updated: 2025/07/02 19:01:17 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"
# include "shell.h"

typedef enum s_err_ctx
{
	GENERAL,
	EXEC
}	t_err_ctx;

typedef int	(*t_error_fn)(int code, char *context);

typedef struct s_error
{
	int			code;
	t_error_fn	fn;
}	t_error;

bool	check_unmached_quotes(char *line);
bool	last_pipe_error(char *line);
bool	first_pipe_error(char *line);
char	*join_input(char *line, int *flag, t_shell *shell);
int		check_input(char *line, t_session *session);

/* -------------------------------------------------------------------------- */

int		check_error(int err_code, char *context, t_err_ctx ctx);

/* -------------------------------------------------------------------------- */

int		handle_cmd_not_found(int code, char *context);
int		handle_bad_subs(int code, char *context);
int		handle_syntax_error(int code, char *context);
int		handle_execute_error(int code, char *context);
int		handle_redirect_fail(int code, char *context);
int		handle_token_error(int code, char *context);
int		handle_cd_error(int code, char *context);
int		handle_is_dir(int code, char *context);
int		handle_export_err(int code, char *context);
int		handle_env_err(int code, char *context);

#endif