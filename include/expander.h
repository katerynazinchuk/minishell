/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:50:36 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/06 13:09:28 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define EXPANDER_H
# include "minishell.h"

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

#endif