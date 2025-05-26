/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:50:36 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/25 13:26:30 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env_type
{
	char				*key;
	char				*value;
	struct s_env_type	*next;
}	t_env_type;

typedef struct s_env_list
{
	t_env_type	*head;
	t_env_type	*tail;
}	t_env_list;

void		add_env_node(t_env_list *env_list, t_env_type *node);
t_env_list	*fill_env_list(char **env);
void		free_env_list(t_env_list *env_list);
void		malloc_error(int *last_exit_status);
void		free_env_node(t_env_type *node);
t_env_type	*fill_env_node(char *str);

#endif