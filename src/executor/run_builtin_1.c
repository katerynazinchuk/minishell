/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:58:42 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/12 15:47:58 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	old_path[PATH_MAX];
	char	new_path[PATH_MAX];
	int	flag[3];
	
	if (!getcwd(old_path, PATH_MAX))
	{
		old_path = ft_strdup("");
		if (!old_path)
			return (ENOMEM) ;
	}
	if (chdir(*(argv + 1)) == -1 )
	{
		error ;//errno seted up
		free(old_path);
		return (-1);
	}
	if (!getcwd(new_path, PATH_MAX))
	{
		free(old_path);
		return (-1);
	}
	flag[1] = update_env_list("OLDPATH", env_list, old_path);
	flag[2] = update_env_list("PWD", env_list, new_path);
	if(!flag[1] || !flag[2])
		return (ENOMEM);
	return (0);
}

int		builtin_pwd(char **argv, t_env_list *env_list)
{
	(void)argv;
	(void)env_list;
	return (0);
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