#ifndef MY_SIGNAL_H
# define MY_SIGNAL_H

# include <signal.h>

typedef enum e_sigtype
{
	MAIN_SIG,
	HEREDOC_SIG,
	DEFAULT_SIG,
} t_sigtype;

void sigint_main(int signal_type);
void sigint_heredoc(int signal_type);
void setsignal(t_sigtype type);

#endif