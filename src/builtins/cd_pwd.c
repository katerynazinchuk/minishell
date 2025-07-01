/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:06:33 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/01 12:23:18 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **argv, t_env_list *env_list)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	(void)env_list;
	if (!argv[1])
		return (check_error(CD_ERR, "path required", GENERAL));
	if (argv[2])
		return (check_error(CD_ERR, "too many arguments", GENERAL));
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (check_error(errno, \
"cannot access current directory", GENERAL));
	if (chdir(argv[1]) == -1)
		return (check_error(errno, argv[1], GENERAL));
	if (getcwd(new_pwd, sizeof(new_pwd)))
	{
		set_env(env_list, "OLDPWD", old_pwd);
		set_env(env_list, "PWD", new_pwd);
	}
	return (0);
}

int	builtin_pwd(char **argv, t_env_list *env_list)
{
	char	cwd[PATH_MAX];

	(void)argv;
	(void)env_list;
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	return (check_error(errno, "cannot access current directory", GENERAL));
}
