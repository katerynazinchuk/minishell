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

void	handle_sigint(int sig)
{
	//char	prompt[1024];

	(void)sig;
	rl_replace_line("", 0);//clean current line
	//write(1, "\nminishell", 12);//just test case
	//update_prompt(prompt);
	//write(1, "\n", 3)
	//write(1, prompt, ft_strlen(prompt));
	rl_on_new_line();
	rl_redisplay();
}

// ctrl-backslash, nothing to do

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
