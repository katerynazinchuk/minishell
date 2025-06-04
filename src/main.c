/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:11:01 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/04 14:45:54 by tchernia         ###   ########.fr       */
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

/* maybe better to move *shell from structure session or not */
//TODO fork() тягне алоковані структури в свої процеси, тому до них завжди має бути доступ, щоб почистити перед execve
void	run_shell(t_shell *shell)
{
	t_session	session;

	init_session(&session, shell);

	while(1)
	{
		update_prompt(&session.prompt);
		session.line = readline(session.prompt);
		//check last pipe
		if (!session.line)
		{
			write(1, "exit\n", 5);
			cleanup_cycle(&session);
			break ;
		}
		cleanup_cycle(&session);
		if (!process_line(&session))
		{
			cleanup_cycle(&session);
			free_ast(session.ast);//TODO воно тут точно існує?
			continue ;
		}
		free_ast(session.ast);
	}
}

bool	process_line(t_session *session)
{
	if (!parser(session))
		return (false);
	//(переїхав в executor) heredoc expand if not commanf  call left and right. -> rewrite 
	add_history(session->line);
	write(1, "run ast\n", 9);
	
	// executor(session->ast, session->shell);
	printf("\n");
	print_node(session->ast, 0);
	return (true);
}

bool	parser(t_session *session)
{
	if(!lexer(session))
	{
		malloc_error(&session->shell->last_exit_status);
		return (false);
	}
	session->ast = build_tree(session->tokens->head, session->tokens->tail);
	if(!session->ast)
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