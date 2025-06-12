/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Amirre <Amirre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:41:32 by Amirre            #+#    #+#             */
/*   Updated: 2025/06/13 00:34:45 by Amirre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* if error_cose < 200 treat it as errno with perror 
	else its our error codes so we need dispatch table for it - if it possible cause 
	in dispatch we use or enum or from 0 and next is +1,
	for int 200 we can only make atoi and ther char 200 (?)*/

static t_error_fn	get_error_fn(int errno);

//maybe when I have malloc_error I need to set errno inside function to show exaxtly malloc? like if (errno == ENOMEM) {errno = ENOMEM} perror(context); 
// or always I can set errno = code;
int	check_error(int code, char *context, int exit_status, int should_return)
{
	t_error_fn	fn;
	
	if (code >= 200)
	{
		fn = get_error_fn(code);
		if (fn)
			return (fn(code, context, exit_status, should_return));
		else
			return (1);
	}
	else
	{
		perror(msg);
		if (code == ENOMEM)
			return (ENOMEM);//i need to track critical error to make exit from my minishell
		return (1);//need to track how I go upper in code to finish this cycle and clean all
	}
 
}

static t_error_fn	get_error_fn(int errno)
{
	static const t_error error[] = {
	{200, command_not_found},
	{201, bad_subs}
	{202, syntax_error},
	{NULL, NULL}
	};
	int	i;
	
	i = 0;
	while (error[i].code)
	{
		if (error[i].code == errno)
			return (error[i].fn);
		i++;
	}
	return (NULL);
}

int	commant_not_found(int code, char *context)
{
	
	return (1);
}

int	bad_subs(int code, char *context)
{
	return (1);
}

int	syntax_error(int code, char *context)
{
	return (1);
}