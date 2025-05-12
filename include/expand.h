/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:34:24 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/12 17:03:14 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

#include "minishell.h"


typedef struct s_expand_type
{
	char	*res;
	char	*var;
	char	*str;
	size_t	len_var;
	int		j;
	int		i;
}	t_expand_type;

// char	*expand_value(char *raw, t_shell_type *shell);
void	expand_tokens(t_token_list *list, t_env_list *env_list);
void	*my_realloc(void *ptr, size_t old_size, size_t new_size);
char	*extract_var(char *raw, size_t *len);
void	init_exp(t_expand_type *exp, char *raw);
bool	is_valid_var(char *var);
bool	check_subs(char *raw);
char	*expand_value(char *raw, t_env_list *env_list);
void	append_exp_str(t_expand_type *exp);
char	*expand_var(char *var, int len, t_env_list *env_list);


#endif