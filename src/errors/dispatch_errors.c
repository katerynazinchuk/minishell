/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:41:32 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/26 13:30:37 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_error_fn	get_error_fn(int err_code);
static t_error_fn	get_syntax_fn(int err_code);
static t_error_fn	get_execute_fn(int err_code);
static int			handle_std_error(int err_code, char *context, \
										t_err_ctx ctx);

int	check_error(int err_code, char *context, t_err_ctx ctx)
{
	t_error_fn	fn;

	if (err_code >= 200)
	{
		fn = get_error_fn(err_code);
		if (fn)
			return (fn(err_code, context));
		else
		{
			ft_putstr_fd("Error not found\n", 2);
			return (1);
		}
	}
	else
		return (handle_std_error(err_code, context, ctx));
}

static	t_error_fn	get_error_fn(int err_code)
{
	if (err_code < 250)
		return (get_syntax_fn(err_code));
	else
		return (get_execute_fn(err_code));
	return (NULL);
}

static t_error_fn	get_syntax_fn(int err_code)
{
	static const t_error	error[] = {
	{SYNTAX_ERR, handle_syntax_error},
	{TOKEN_ERR, handle_token_error},
	{BAD_SUBS, handle_bad_subs},
	{0, NULL}
	};
	int						i;

	i = 0;
	while (error[i].code)
	{
		if (error[i].code == err_code)
			return (error[i].fn);
		i++;
	}
	return (NULL);
}

static t_error_fn	get_execute_fn(int err_code)
{
	static const t_error	error[] = {
	{EXECUTE_ERR, handle_execute_error},
	{REDIRECT_FAIL, handle_redirect_fail},
	{CMD_NOT_FOUND, handle_cmd_not_found},
	{CD_ERR, handle_cd_error},
	{IS_DIR, handle_is_dir},
	{0, NULL}
	};
	int						i;

	i = 0;
	while (error[i].code)
	{
		if (error[i].code == err_code)
			return (error[i].fn);
		i++;
	}
	return (NULL);
}

static int	handle_std_error(int err_code, char *context, t_err_ctx ctx)
{
	int		status;
	char	msg[PATH_MAX];

	ft_strlcpy(msg, "minishell : ", PATH_MAX);
	if (err_code == ENOMEM)
		errno = ENOMEM;
	if (ctx == GENERAL)
		status = 1;
	else
	{
		if (errno == ENOENT)
			status = 127;
		else
			status = 126;
	}
	if (context)
		ft_strlcat(msg, context, PATH_MAX);
	perror(msg);
	return (status);
}
