/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:36:16 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/01 17:41:13 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	sigint_main(int signal_type)
{
	g_signal = signal_type;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_heredoc(int signal_type)
{
	g_signal = signal_type;
	rl_done = 1;
}

void	setsignal(t_sigtype type)
{
	if (type == MAIN_SIG)
	{
		signal(SIGINT, sigint_main);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == HEREDOC_SIG)
	{
		signal(SIGINT, sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
