/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:54:28 by tchernia          #+#    #+#             */
/*   Updated: 2025/07/01 11:34:46 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static int	is_cmd_path(char **pathes, char **val, char *cmd);
static int	check_pathes(t_env_list *env_list, char ***pathes);
static int	check_access(char *cmd);

int	find_path(char **value, t_env_list *env_list)
{
	char	**pathes;
	char	**keep_start;
	char	*cmd;
	int		status;

	cmd = value[0];
	if (ft_strchr(cmd, '/'))
	{
		status = check_access(cmd);
		if (status)
			return (status);
	}
	if (check_pathes(env_list, &pathes))
		return (1);
	keep_start = pathes;
	while (*pathes && !is_cmd_path(pathes, &value[0], cmd))
		pathes++;
	free_arr(keep_start);
	if (errno == ENOMEM)
		return (1);
	return (0);
}

static int	check_pathes(t_env_list *env_list, char ***pathes)
{
	char	*env_value;

	if (!get_env_value("PATH", env_list, &env_value))
		return (1);
	*pathes = ft_split(env_value, ':');
	if (!*pathes)
		return (check_error(ENOMEM, "execute", GENERAL));
	return (0);
}

static int	is_cmd_path(char **pathes, char **val, char *cmd)
{
	char	full_path[PATH_MAX];
	int		len_path;

	ft_strlcpy(full_path, *pathes, PATH_MAX);
	ft_strlcat(full_path, "/", PATH_MAX);
	ft_strlcat(full_path, cmd, PATH_MAX);
	if (access(full_path, X_OK) == 0)
	{
		errno = 0;
		len_path = ft_strlen(full_path) + 1;
		*val = my_realloc(*val, ft_strlen(*val) + 1, len_path);
		if (*val)
			ft_strlcpy(*val, full_path, len_path);
		return (1);
	}
	return (0);
}

static int	check_access(char *cmd)
{
	struct stat	sb;

	if (stat(cmd, &sb) == -1)
		return (check_error(errno, cmd, EXEC));
	if (S_ISDIR(sb.st_mode))
		return (check_error(IS_DIR, cmd, EXEC));
	if (access(cmd, X_OK) == -1)
		return (check_error(EACCES, cmd, EXEC));
	return (0);
}
