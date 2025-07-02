/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:11:01 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/02 17:49:50 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	if (init_shell(&shell, env))
		return (1);
	ignore_args(argc, argv);
	setsignal(MAIN_SIG);
	run_shell(&shell);
	destroy_shell(&shell);
	destroy_shell(&shell);
	return (shell.status);
}

void	run_shell(t_shell *shell)
{
	t_session	session;

	init_session(&session, shell);
	while (shell->env_list->is_run)
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
		return (0);
	rl_event_hook = NULL;
	input_status = check_input(readline(session->prompt), session);
	add_history(session->line);
	if (g_signal != 0)
	{
		session->shell->status = 128 + g_signal;
		g_signal = 0;
	}
	if (input_status == 1)
		return (shell_exit(session));
	else if (input_status != 0)
		return (0);
	setsignal(MAIN_SIG);
	if (process_line(session))
		free_for_fork(session);
	free_ast(&session->ast);
	return (0);
}

int	process_line(t_session *session)
{
	if (parser(session))
		return (1);
	heredoc(session->ast, session);
	if (g_signal != 0)
		return (g_signal = 0, 1);
	free_for_fork(session);
	executor(session);
	if (session->shell->status == 131)
		ft_putendl_fd("Quit", 1);
	return (0);
}

int	parser(t_session *session)
{
	if (lexer(session))
		return (1);
	session->ast = parse_pipe(session->tokens->head, session->tokens->tail);
	if (!session->ast)
	{
		return (1);
	}
	return (0);
}
