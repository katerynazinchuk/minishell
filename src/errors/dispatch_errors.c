/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Amirre <Amirre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:41:32 by Amirre            #+#    #+#             */
/*   Updated: 2025/06/17 20:12:30 by Amirre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_error_fn	get_error_fn(int err_code);
static t_error_fn	get_syntax_fn(int err_code);
static t_error_fn	get_execute_fn(int err_code);

//maybe when I have malloc_error I need to set errno inside function to show exaxtly malloc? like if (errno == ENOMEM) {errno = ENOMEM} perror(context); 
// or always I can set errno = code;
int	check_error(int err_code, char *context)
{
	t_error_fn	fn;
	
	if (err_code >= 200)
	{
		fn = get_error_fn(err_code);
		if (fn)
			return (fn(err_code, context));
		else
			return (1);//ft_putstr("Error not found\n");
	}
	else
	{
		if (err_code == ENOMEM)
			errno = ENOMEM;
		perror(context);
		// if (err_code == ENOMEM)
		// 	return (ENOMEM);//i need to track critical error to make exit from my minishell
		return (1);//need to track how I go upper in code to finish this cycle and clean all
	}
 
}
// hash map (?) hash table
static t_error_fn	get_error_fn(int err_code)
{
	if (err_code < 250)
		return (get_syntax_fn(err_code));
	else
		return (get_execute_fn(err_code));
	return (NULL);
}

/* here we set syntax errors */
static t_error_fn	get_syntax_fn(int err_code)
{
	static const t_error error[] = {
		{SYNTAX_ERROR, handle_syntax_error},
		{BAD_SUBS, handle_bad_subs},
		{0, NULL}
		};
	int							i;
	
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
	static const t_error error[] = {
		{EXECUTE_ERROR, handle_execute_error},
		{REDIRECT_FAIL, handle_redirect_fail},
		{CMD_NOT_FOUND, handle_cmd_not_found},
		{0, NULL}
		};
	int							i;
	
	i = 0;
	while (error[i].code)
	{
		if (error[i].code == err_code)
			return (error[i].fn);
		i++;
	}
	return (NULL);
}
/* here we set execute errors 
static t_error_fn	get_execute_fn(int err_code)
{
	static const t_error error[] = {
		{200, command_not_found},
		{201, bad_subs},
		{202, syntax_error},
		{NULL, NULL}
		};
	int							i;
	
	i = 0;
	while (error[i].code)
	{
		if (error[i].code == err_code)
			return (error[i].fn);
		i++;
	}
	return (NULL);
} */

/* static const t_error_fn error[] = {
	[SYNTAX_ERROR] = syntax_error
	[BAD_SUBS] = bad_subs,
	[EXECUTE_ERROR] = execute_error,
	[REDIRECT_FAIL] = redirect_fail,
	[CMD_NOT_FOUND] = command_not_found,
	}; */