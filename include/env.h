/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:50:36 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/06 18:09:16 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char		*key;
	char		*value;
	t_env_type	*next;
}	t_env_type;

typedef struct s_env_list
{
	t_env_type	*head;
	t_env_type	*tail;
}	t_env_list;

void	add_env_node(t_env_list *env_list, t_env_type *node);
void	fill_env_list(char **env);
void	free_env_list(t_env_list *env_list);
void	malloc_error(void);
void	free_env_node(t_env_type *node);

#endif