/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:07:56 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/29 18:03:35 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_execute(t_execute *exe)
{
	// exe->shell = session->shell;
	// exe->ast = session->ast;
	exe->fd[0] = -1;
	exe->fd[1] = -1;
	// int			prev_fd;
	// t_list		*pid_list;
	// t_list		*heredoc_fds;
}

void	init_cmd_info(t_cmd_info *cmd_info, t_execute *exe)
{
	(void)exe;
	cmd_info->argv = NULL;            // command + arguments
	cmd_info->infile = NULL;           // for `<`
	cmd_info->outfile = NULL;          // for `>` or `>>`
	cmd_info->append_mode = 1;        // 1 if >>, 0 if >
	cmd_info->is_heredoc = 1;         // 1 if heredoc, 0 otherwise
	cmd_info->heredoc_delim = NULL;    // heredoc delimiter
	//struct s_command	*next; // next in pipe chain
}

bool	is_builtin(t_cmd_info *cmd_info, t_shell *shell, t_execute *exe)
{
	(void)cmd_info;
	(void)shell;
	(void)exe;
	return (true);
}

static char	*to_str(t_env_type *cur)
{
	size_t	len;
	char	*str;
	len = ft_strlen(cur->key) + ft_strlen(cur->value) + 1;//1 for =
	str = ft_calloc(sizeof(char), len + 1);//1 for '\0'
	if (!str)
		return (NULL);
	ft_strlcat(str, cur->key, len + 1);
	ft_strlcat(str, "=", len + 1);
	ft_strlcat(str, cur->value, len + 1);
	return (str);
}

char **env_to_arr(t_env_list *env_list)
{
	char		**env_arr;
	t_env_type	*current;
	size_t		i;
	
	env_arr = (char **)ft_calloc(sizeof(char *), env_list->size + 1);
	if (!env_arr)
		return (NULL);
	current = env_list->head;
	i = 0;
	while (current)
	{
		env_arr[i] = to_str(current);
		if (!env_arr[i])
		{
			while(i)
			{
				i--;
				free(env_arr[i]);
			}
			free(env_arr);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	return (env_arr);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*full_path(char *cmd, t_env_list *env_list)
{
	char	**e_path;
	char	path[PATH_MAX];
	char	*dup_path;
	char	**keep_start;
	char	*value;

	if (!get_env_value("PATH", env_list, &value))
		return (NULL);
	e_path = ft_split(value, ':');
	if (!e_path || !e_path[0])
		return (NULL);
	keep_start = e_path;
	while (*e_path)
	{
		ft_strlcpy(path, *e_path, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, cmd, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			dup_path = ft_strdup(path);
			free(value);
			free_arr(keep_start);
			return (dup_path);
		}
		e_path++;
	}
	free(value);
	free_arr(keep_start);
	return (NULL);
}

