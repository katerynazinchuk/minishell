/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:58:42 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/16 17:14:12 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cat << k > 1.txt | ls | > 2.txt

t_builtin_fn	get_builtin_fn(char *cmd)
{
	static const t_builtin	builtin[] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{NULL, NULL}
	};
	int						i;

	i = 0;
	while (builtin[i].name)
	{
		if (ft_strcmp(cmd, builtin[i].name) == 0)
			return (builtin[i].func);
		i++;
	}
	return (NULL);
}

int	builtin_echo(char **argv, t_env_list *env_list)
{
	int		new_line;

	(void)env_list;
	argv++;
	new_line = 1;
	while(*argv && is_new_line(*argv))
	{
		new_line = 0;
		argv++;
	}
	while (*argv)
	{
		ft_putstr_fd(*argv, 1);
		if (*(argv + 1))
			write(1, " ", 1);
		argv++;
	}
	if (new_line)
		write(1, "\n", 1);
	return (0);
}

int	builtin_cd(char **argv, t_env_list *env_list)
{
	(void)argv;
	(void)env_list;
	return (0);
}

int		builtin_pwd(char **argv, t_env_list *env_list)
{
	char	cwd[PATH_MAX];
	
	(void)argv;
	(void)env_list;
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	perror("pwd");
	return (1);
}

int		builtin_export(char **argv, t_env_list *env_list)
{
	(void)argv;
	(void)env_list;
	return (0);
}

/* int	run_builtin(t_ast_node *node, t_shell *shell)
{
	static const t_builtin_fn	builtins[] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{NULL, NULL}
	};
	int								i;

	i = 0;
	while (builtins[i].name)
	{
		if(ft_strcmp(argv[0], builtins[i].name) == 0)
			return (builtins[i].func(argv, env_list));
		i++;
	}
	return(1);
} */