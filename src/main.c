/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:11:01 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/09 15:44:48 by kzinchuk         ###   ########.fr       */
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
	t_session	session;

	init_session(&session, shell);

	while(1)
	{
		update_prompt(&session.prompt);
		//session.line = readline(session.prompt);
		session.line = check_input(readline(session.prompt)); //clarify this logic, cos now it mixing all together
		if (!session.line)
		{
			write(1, "exit\n", 5);
			free_for_fork(&session);
			break ;
		}
		if (!process_line(&session))
		{
			free_ast(session.ast);
			free_for_fork(&session);
			continue ;
		}
		if(session.ast)
			free_ast(session.ast);
	}
}

bool	process_line(t_session *session)
{
	if (!parser(session))
		return (false);
	add_history(session->line);
	heredoc(session->ast, session);
	//heredoc expand if not commanf  call left and right. -> rewrite 
	free_for_fork(session);
	//execute
	return (true);
}

bool	parser(t_session *session)
{
	if(!lexer(session))
	{
		return (false);
	}
	
	session->ast = parse_pipe(session->tokens->head, session->tokens->tail);
	
	if(!session->ast)
	{
		// TODO need to manage errors, maybe do it with return like write 
		return (false);
	}
	print_node(session->ast, 0);
	return (true);
}
