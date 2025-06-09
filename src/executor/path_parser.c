/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:54:28 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/09 19:02:17 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verify_cmd_path(char **pathes, char **val, const char *cmd, int *f);
static int	check_pathes(t_env_list *env_list, char ***pathes);

/* need to decide with return value to track malloc errors */
int	find_path(char **value, t_env_list *env_list)
{
	char		**pathes;
	char		**keep_start;
	const char	*cmd;
	int			flag;

	cmd = value[0];
	if (!check_pathes(env_list, &pathes))
		return (0);
	keep_start = pathes;
	flag = 0;
	while (*pathes)
	{
		if (verify_cmd_path(pathes, &value[0], cmd, &flag))
			break ;
		pathes++;
	}
	free_arr(keep_start);
	if (flag)
		return (0);//malloc error
	return (1);
}

/* 	flag = get_env_value("PATH", env_list, &env_value);
	if (flag == 2)
		return (0);
	else if (flag == 0)
		return (1);//execve will process error with "path not found"
	pathes = ft_split(env_value, ':');
	if (!pathes)
		return (0);//malloc error */


static int	check_pathes(t_env_list *env_list, char ***pathes)
{
	char	*env_value;

	if (!get_env_value("PATH", env_list, &env_value))
		return (1);//execve will process error with "path not found"
	*pathes = ft_split(env_value, ':');
	if (!*pathes)
		return (0);//malloc error
	return (1);
}


static int	verify_cmd_path(char **pathes, char **val, const char *cmd, int *f)
{
	char		full_path[PATH_MAX];
	int			len_path;

	*f = 0;
	ft_strlcpy(full_path, *pathes, PATH_MAX);
	ft_strlcat(full_path, "/", PATH_MAX);
	ft_strlcat(full_path, cmd, PATH_MAX);
	if (access(full_path, X_OK) == 0)
	{
		len_path = ft_strlen(full_path) + 1;
		*val = my_realloc(*val, ft_strlen(*val) + 1, len_path);
		if (!*val)
		{
			*f = 1;
			return (2);//як трекати помилку маллок.
		}
		ft_strlcpy(*val, full_path, len_path);
		return (1);
	}
	return (0);
}

/* static char	*build_and_check_path(char **pathes, char *cmd, int *error_code);

bool	find_path(char **value, t_env_list *env_list)
{
	char	**pathes;
	char	*full_path;
	char	**keep_start;
	char	*env_value;

	if (!get_env_value("PATH", env_list, &env_value))
		return (NULL);
	pathes = ft_split(env_value, ':');
	if (!pathes || !pathes[0])//TODO do we need to set error code?
		return (NULL);
	keep_start = pathes;
	full_path = NULL;
	while (*pathes)
	{
		full_path = build_and_check_path(pathes, value);
		if (full_path)
			break ;
		pathes++;
	}
	free(env_value);
	free_arr(keep_start);
	return (full_path);
} */

/*  we need to track error_codes 
static char	*build_and_check_path(char **pathes, char *cmd, int *error_code)
{
	char	path[PATH_MAX];
	char	*full_path;
	
	ft_strlcpy(path, *pathes, PATH_MAX);
	ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, cmd, PATH_MAX);
	if (access(path, X_OK) == 0)
	{
		full_path = ft_strdup(path);
		if(!full_path)
		{
			*error_code = ENOMEM;
			return(NULL);
		}
		*error_code = 0;
		return (full_path);
	}
	else
	{
		*error_code = 200;//our personal error code for "command not found"
		return (NULL);
	}
} */

/* static char	*build_and_check_path(char **pathes, char *cmd, int *error_code);

char	*find_path(char *cmd, t_env_list *env_list, int error_code)
{
	char	**pathes;
	char	*full_path;
	char	**keep_start;
	char	*env_value;

	if (!get_env_value("PATH", env_list, &env_value))
		return (NULL);
	pathes = ft_split(env_value, ':');
	if (!pathes || !pathes[0])//TODO do we need to set error code?
		return (NULL);
	keep_start = pathes;
	full_path = NULL;
	while (*pathes)
	{
		full_path = build_and_check_path(pathes, cmd, &error_code);
		if (full_path)
			break ;
		pathes++;
	}
	free(env_value);
	free_arr(keep_start);
	return (full_path);
}

 we need to track error_codes 
static char	*build_and_check_path(char **pathes, char *cmd, int *error_code)
{
	char	path[PATH_MAX];
	char	*full_path;
	
	ft_strlcpy(path, *pathes, PATH_MAX);
	ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, cmd, PATH_MAX);
	if (access(path, X_OK) == 0)
	{
		full_path = ft_strdup(path);
		if(!full_path)
		{
			*error_code = ENOMEM;
			return(NULL);
		}
		*error_code = 0;
		return (full_path);
	}
	else
	{
		*error_code = 200;//our personal error code for "command not found"
		return (NULL);
	}
} */


