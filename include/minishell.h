/* Дозволені функції
a: access, add_history
c: chdir, close, closedir
d: dup, dup2
e: execve, exit
f: fork, free, fstat
g: getcwd, getenv
i: ioctl, isatty
k: kill
l: lstat
m: malloc
o: open, opendir
p: perror, pipe, printf
r: read, readdir, readline, rl_clear_history, rl_on_new_line, rl_redisplay, rl_replace_line
s: sigaction, sigaddset, sigemptyset, signal, stat, strerror
t: tcgetattr, tcsetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs, ttyname, ttyslot
u: unlink
w: wait, wait3, wait4, waitpid, write 
*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include "my_signal.h"
# include "libft.h"
# include <errno.h>
# include "errors_enum.h"
# include "errors.h"
# include "dispatch_errors.h"
# include "error_fn.h"
# include "libft.h"
# include "env.h"
# include "utils.h"
# include "token.h"
# include "shell.h"
# include "expand.h"
# include "lexer.h"
# include "parser.h"
# include "heredoc.h"
# include <limits.h>
# include "executor.h"
# include <limits.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <pwd.h>
# include <sys/types.h>

extern volatile sig_atomic_t g_signal;

int	ft_strcmp(const char *str1, const char *str2);
int	ft_strcmp(const char *str1, const char *str2);

#endif