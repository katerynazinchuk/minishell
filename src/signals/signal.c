#include "minishell.h"

/* Need correction/addition when we will work with fork
we need to return signals back into default-system
	pid==0
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve();

ignore or process signals in parent to avoid fall down shell
after finishing child proc we need to process status in good way
	if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
without it could kill shell or give back strange symbols insted prompt
*/

//Ctrl-C
sig_atomic_t g_signal = 0;


typedef enum e_sigtype
{
	MAIN_SIG,
	HEREDOC_SIG,
	DEFAULT_SIG
} t_sigtype;

// For main readline
void sigint_main(int signal_type)
{
	g_signal = signal_type;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void sigint_heredoc(int signal_type)
{
	g_signal = signal_type;
	rl_done = 1;
}

void setsignal(t_sigtype type)
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
		signal(SIGINT,SIG_DFL);
		signal(SIGQUIT, SIG_DFL);		
	}
}

// int main (void)
// {
// 	char *line;
// 	int exit_status = 0;
// 	setsignal(HEREDOC_SIG);
	
// 	while(1)
// 	{
// 		rl_event_hook = event_handler;
// 		line = readline("heredoc> ");
// 		if (line == NULL)
// 			break;
// 		if (g_signal != 0)
// 		{
// 			exit_status = 128 + g_signal;
// 			g_signal = 0;
// 			break;
// 		}
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	setsignal(MAIN_SIG);
// 	return (0);

// }
// Ctrl+C → SIGINT
// Ctrl+\ → SIGQUIT -> SIG_IGN,
// Ctrl+D → EOF

// sigaction, sigemptyset, sigadd

//  0010
//  0001
// |0011

