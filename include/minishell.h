/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:58:48 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/02 19:05:07 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include "my_signal.h"
# include "libft.h"
# include <errno.h>
# include "errors_enum.h"
# include "errors.h"
# include "libft.h"
# include "env.h"
# include "token.h"
# include "parser.h"
# include "shell.h"
# include "utils.h"
# include "expand.h"
# include "lexer.h"
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

extern volatile sig_atomic_t	g_signal;

int	ft_strcmp(const char *str1, const char *str2);

#endif