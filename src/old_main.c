/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:11:01 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/19 19:16:40 by tchernia         ###   ########.fr       */
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

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --suppressions=readline.supp ./minishell

*/

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	
	init_shell(&shell, env);
	if (!shell.env_list)
	{
		malloc_error(&shell.status);
		return (shell.status);
	}
	(void)argc;
	(void)argv;
	setsignal(MAIN_SIG);
	run_shell(&shell);
	free_env_list(shell.env_list);
	shell.env_list = NULL;
	return(shell.status);
}

void	run_shell(t_shell *shell)
{
	t_session	session;

	init_session(&session, shell);
	
	while(1)
	{
		update_prompt(&session.prompt);
		session.line = check_input(readline(session.prompt));
		if (!session.line)
		{
			write(1, "exit\n", 5);
			free_for_fork(&session);
			break ;
		}
		if (SIGINT == 2)
		{
			setsignal(MAIN_SIG);
		}
		if (!process_line(&session))
		{
			free_for_fork(&session);
			free_ast(session.ast);
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
	if (g_signal != 0)
		return (g_signal = 0, false);
	free_for_fork(session);
	executor(session);
	return (true);
}

bool	parser(t_session *session)
{
	if(!lexer(session))
		return (false);
	session->ast = parse_pipe(session->tokens->head, session->tokens->tail);
	if(!session->ast)
	{
		return (false);
	}
	print_node(session->ast, 0);
	return (true);
}
