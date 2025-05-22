/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:11:01 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/22 13:37:16 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_env_list(t_env_list *env_list);
/* [username@hostname current_working_directory]$ */
//readline return NULL, so (!line) processing case when we use Ctrl+D

/* --leak-check=full
valgrind --leak-check=full --show-leak-kinds=all ./minishell

valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

*/

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	
	init_shell(&shell, env);
	(void)argc;
	(void)argv;
	// init_signals();

	while(1)
	{
		//update_prompt(prompt);
		shell.line = readline(shell.prompt);
		if (!shell.line)
		{
			free_shell(&shell);
			write(1, "exit\n", 4);
			exit (0);
		}
		if(*shell.line)
		{
			shell.tokens = fill_tokens(shell.line);
			if (shell.tokens)
			{
				expand_tokens(&shell);//move it to fill_tokens
				// print_tokens(&shell);
				shell.ast = build_tree(shell.tokens->head, shell.tokens->tail);
				
				if(shell.ast)
				{
					//heredoc expand if not commanf  call left and right. -> rewrite 
					//execute
					printf("\n");
					print_node(shell.ast, 0);
					// print_ast(shell.ast, 0);
					// print_redir_tree(shell.ast);
					// print_argv(shell.ast->value);
					free_ast(shell.ast);
				}
				free_token_list(shell.tokens);
			}
			// add_history(shell.line);
		}
		// if (*line)
		// 	add_history(line);
		// printf("command: %s\n", shell.line);
		free(shell.line);
	}
	write(1, "here\n", 5);
	print_env_list(shell.env_list);
	// print_shell(&shell);
	free_shell(&shell);
	// print_shell(&shell);
	return(0);
}


