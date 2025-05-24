/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:35:39 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/22 15:24:31 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// void	init_shell(t_shell_type *shell)

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	init_shell(&shell);
	shell.env_list = fill_env_list(env);
	if (!shell.env_list)
		return (1);//check exit & returns inside func
	run_shell(&shell);
	free_shell(&shell);
	return (0);
}

void	run_shell(t_shell_type	*shell)
{
	while (1)
	{
		shell->line = readline(shell->prompt);
		if (!shell->line)
			break;//status echo$ ?
		// if (*shell->line)
		// 	add_history(shell->line)
		shell->token_list = lexer(shell->line, shell);
		if (!shell->token_list)
		{
			free(shell->line);
			continue ;
		}
		// shell->ast = parse(shell->token_list);//we need to allocate memory inside
		// if (!shell->ast)
		// {
		// 	free_token_list(shell->token_list);
		// 	free(shell->line);
		// 	continue ;
		// }
		// execute(shell->ast);//do we need to free line&token_list in case of error?
		cleanup_cycle(shell);
	}
}



