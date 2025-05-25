/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:11:01 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/25 13:24:36 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* [username@hostname current_working_directory]$ */

//readline return NULL, so (!line) processing case when we use Ctrl+D

/*
--leak-check=full
--track-origins=yes

valgrind --leak-check=full --show-leak-kinds=all ./minishell

valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp ./minishell

*/

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	
	init_shell(&shell, env);
	if (!shell.env_list)
	{
		malloc_error(&shell.last_exit_status);
		return (shell.last_exit_status);
	}
	(void)argc;
	(void)argv;
	// init_signals();
	run_shell(&shell);
	free_env_list(shell.env_list);
	shell.env_list = NULL;
	return(shell.last_exit_status);
}

void	run_shell(t_shell *shell)
{
	while(1)
	{
		//update_prompt(prompt);
		shell->line = readline(shell->prompt); 
		if (!shell->line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (!process_line(shell))
		{
			cleanup_cycle(shell);
			continue ;
		}
		cleanup_cycle(shell);
	}
}

bool	process_line(t_shell *shell)
{
	if (!parser(shell))
		return (false);
	//heredoc expand if not commanf  call left and right. -> rewrite 
	//execute
	printf("\n");
	print_node(shell->ast, 0);
	add_history(shell->line);
	return (true);
}

bool	parser(t_shell *shell)
{
	if(!lexer(shell))
	{
		malloc_error(&shell->last_exit_status);
		return (false);
	}
	shell->ast = build_tree(shell->tokens->head, shell->tokens->tail);
	if(!shell->ast)
	{
		// TODO need to manage errors, maybe do it with return like write 
		return (false);
	}
	return (true);
}
/* void	run_shell(t_shell *shell)
{
	while(1)
	{
		//update_prompt(prompt);
		shell->line = readline(shell->prompt); 
		if (!shell->line)
		{
			write(1, "exit\n", 5);//TODO do we need clean here or cleanup enough?
			break ;
		}
		if(shell->line)
		{
			if(!lexer(shell))
			{
				
			}
			// shell->tokens = lexer(shell);
			// print_tokens(&shell);
			if (shell->tokens)
			{
				shell->ast = build_tree(shell->tokens->head, shell->tokens->tail);
				if(shell->ast)
				{
					//heredoc expand if not commanf  call left and right. -> rewrite 
					//execute
					printf("\n");
					print_node(shell->ast, 0);
					// print_ast(shell->ast, 0);
					// print_redir_tree(shell->ast);
					// print_argv(shell->ast->value);
					// free_ast(shell->ast);
					// shell->ast = NULL;
				}
				// free_token_list(shell->tokens);
				// shell->tokens = NULL;
			}
			add_history(shell->line);
		}
		cleanup_cycle(shell);
		// printf("command: %s\n", shell->line);
	}
} */