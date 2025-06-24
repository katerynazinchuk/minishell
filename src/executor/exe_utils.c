/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:07:56 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/24 17:33:59 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*to_str(t_env_type *cur)
{
	size_t	len;
	char	*str;

	len = ft_strlen(cur->key) + ft_strlen(cur->value) + 1;//1 for =
	str = ft_calloc(sizeof(char), len + 1);//1 for '\0'
	if (!str)
	{
		check_error(ENOMEM, "executor", GENERAL);
		return (NULL);
	}
	ft_strlcat(str, cur->key, len + 1);
	ft_strlcat(str, "=", len + 1);
	ft_strlcat(str, cur->value, len + 1);
	return (str);
}

char	**env_to_arr(t_env_list *env_list)
{
	char		**env_arr;
	t_env_type	*current;
	size_t		i;
	
	env_arr = (char **)ft_calloc(sizeof(char *), env_list->size + 1);
	if (!env_arr)
	{
		check_error(ENOMEM, "executor", GENERAL);
		return (NULL);
	}
	current = env_list->head;
	i = 0;
	while (current)
	{
		env_arr[i] = to_str(current);
		if (!env_arr[i])
		{
			env_arr[i] = NULL;
			free_arr(env_arr);
			return(NULL);
		}
		i++;
		current = current->next;
	}
	return (env_arr);
}

bool	is_new_line(char *str)
{
	if (!str || str[0] != '-')
		return (false);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (false);
		str++;
	}
	return (true);
}

void	free_arr(char **arr)
{
	size_t	i;

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

void	restore_fd(t_session *session)
{
	dup2(session->shell->fd[STDIN_FILENO], STDIN_FILENO);
	dup2(session->shell->fd[STDOUT_FILENO], STDOUT_FILENO);
}

void	close_pipe_fd(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int	free_in_fork(t_session *session, char **env_arr)
{
	if (env_arr)
		free_arr(env_arr);
	free_env_list(session->shell->env_list);
	free_ast(&session->ast);
	destroy_shell(session->shell);
	return (1);
}