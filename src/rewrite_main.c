/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:11:01 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/20 14:21:38 by tchernia         ###   ########.fr       */
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
		return (check_error(ENOMEM, "can't create env_list"));
	ignore_args(argc, argv);
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
		errno = 0;
		if (shell_loop(&session))
			break ;
		if (errno == ENOMEM)
			break ;
	}
}

int	shell_loop(t_session *session)
{
	int	input_status;
	
	if (update_prompt(&session->prompt))
		return (0);//track enomem to comtinue loop
	input_status = check_input(readline(session->prompt), &session->line);
	if (input_status == 1)
		return(shell_exit(session));
	else if (input_status != 0)
		return (0);
	setsignal(MAIN_SIG);
	if (process_line(session))
		free_for_fork(session);
	if (session->ast)
		free_ast(&session->ast);
	return (0);
}

int	process_line(t_session *session)
{
	if (parser(session))
		return (1);
	add_history(session->line);
	heredoc(session->ast, session);//переписати на int
	if (g_signal != 0)
		return (g_signal = 0, 1);
	free_for_fork(session);
	executor(session);
	return (0);
}

int	parser(t_session *session)
{
	if(lexer(session))
		return (1);
	print_tokens(session);
	session->ast = parse_pipe(session->tokens->head, session->tokens->tail);
	if(!session->ast)
	{
		write(1, "no ast\n", 8);
		return (1);
	}
	print_node(session->ast, 0);
	return (0);
}
