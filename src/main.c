/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:11:01 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/17 12:26:08 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_list(t_env_list *env_list);


/* [username@hostname current_working_directory]$ */

//readline return NULL, so (!line) processing case when we use Ctrl+D

int main(int argc, char **argv, char **env)
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
			write(1, "exit\n", 4);
			exit (0);
		}
		if(*shell.line)
		{
			shell.tokens = fill_tokens(shell.line);
			if (shell.tokens)
			{
				expand_tokens(&shell);//move it to fill_tokens
				print_tokens(&shell);
				shell.ast = build_tree(shell.tokens->head, shell.tokens->tail);
				if(shell.ast)
				{
					print_ast(shell.ast, 0);
					free_ast(shell.ast);
				}
				free_token_list(shell.tokens);
			}
			add_history(shell.line);
		}
		//token = extract_token(lexer, state);
		//parse_tokens(token);
		//execute_command(token);
		// if (*line)
		// 	add_history(line);
		printf("command: %s\n", shell.line);
		free(shell.line);
	}
	free_shell(&shell);
	return(0);
}

void	print_env_list(t_env_list *env_list)
{
	t_env_type	*current;
	
	current = env_list->head;
	while (current)
	{
		printf("key: %s\n value: %s\n\n", current->key, current->value);
		current = current->next;
	}
}
