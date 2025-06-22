/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:58:42 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/22 18:18:06 by tchernia         ###   ########.fr       */
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
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	
	(void)env_list;
	if (!argv[1])
		return (check_error(CD_ERR, "path required", GENERAL));
    // {
    //     ft_putstr_fd("cd: path required\n", 2);
	// 	return (1);
    // }
	if (argv[2])
		return (check_error(CD_ERR, "too many arguments", GENERAL));
	if(!getcwd(old_pwd, sizeof(old_pwd)))
		return (1);
	if (chdir(argv[1]) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (1);
	}
	if (getcwd(new_pwd, sizeof(new_pwd)))
	{
		set_env(env_list, "OLDPWD", old_pwd);
		set_env(env_list, "PWD", new_pwd);
	}
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
void print_export(t_env_list *env_list);
int is_valid_input(char *var);

int		builtin_export(char **argv, t_env_list *env_list)
{
	int		i;
	char	*divider;
	char	*key;
	char	*value;
	
	(void)env_list;
	i = 1;
	if(!argv[1])
	{
		print_export(env_list);
		// return (0);
	}
	while(argv[i])
	{
		if(!is_valid_input(argv[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd("': not a valid identifier\n", 2);
			return(1);
		}
		else
		{
			divider = ft_strchr(argv[i], '=');
			if(divider)
			{
				key = ft_substr(argv[i], 0, divider - argv[i]);
				value = ft_strdup(divider + 1);
				if(!key || !value || set_env(env_list, key, value))
				{
					// malloc_error(&env_list->size);// here or on the upper level???
					// return (1);
					return(ENOMEM);
				}
				free(key);
				free(value);
			}
			else
				set_env(env_list, argv[i], NULL);//NULL
		}
		i++;
	}
	return (0);
}

void print_export(t_env_list *env_list)
{
	t_env_type	*current;

	current = env_list->head;
	while (current)
	{
		if (current->key && current->value)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(current->value, 1);
			ft_putstr_fd("\"", 1);
			write(1, "\n", 1);
		}
		else if( current->key && !current->value)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(current->key, 1);
			write(1, "\n", 1);
		}
		current = current->next;
	}
//return (0);
}

int is_valid_input(char *var)
{
	int i;

	i = 1;
	if(!var || !var[0] || ft_isdigit(var[0]) || (!ft_isalpha(var[0]) && var[0] == '_' ) || var[0] == '=')
	{
		//write(1, &var[i], 1);
		//ft_putstr_fd("export: not a valid identifier\n", 2);
		return (0);
	}

	while(var[i] && var[i] != '=')
	{
		//write(1, &var[i], 1);
		
		if(var[i] != '_' && !ft_isalnum(var[i]))
   			return (0);
		i++;
	}
	return (1);
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