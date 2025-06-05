/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:54:28 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/05 19:00:08 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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