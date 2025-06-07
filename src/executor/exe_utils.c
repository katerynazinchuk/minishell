/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:07:56 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/05 15:42:01 by tchernia         ###   ########.fr       */
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
		return (NULL);
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
		return (NULL);
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
			/* 			while(i)
			{
				i--;
				free(env_arr[i]);
			}
			free(env_arr);
			return (NULL); */
		}
		i++;
		current = current->next;
	}
	return (env_arr);
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



/* 	ft_strlcpy(path, *e_path, PATH_MAX);
	ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, cmd, PATH_MAX);
	if (access(path, X_OK) == 0)
	{
		full_path = ft_strdup(path);
		free(value);
		free_arr(keep_start);
		return (full_path);
	} */