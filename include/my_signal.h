#ifndef SIGNAL_H
# define SIGNAL_H

# include <signal.h>

void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	init_signals(void);

#endif