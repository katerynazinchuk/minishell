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
# include "libft.h"
# include "errors.h"
# include "env.h"
# include "utils.h"
# include "token.h"
# include "shell.h"
# include "expand.h"
# include "lexer.h"
# include "parser.h"
# include "heredoc.h"
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <pwd.h>
# include <sys/types.h>

int	ft_strcmp(const char *str1, const char *str2);

#endif