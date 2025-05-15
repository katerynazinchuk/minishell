/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:34:24 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/15 17:18:10 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

#include "minishell.h"

typedef struct s_expand_type
{
	size_t	len_var;
	size_t	len_raw;
	int		j;
	int		i;
	char	*res;
	char	*var;
	char	*str;
}	t_expand_type;

// char	*expand_value(char *raw, t_shell_type *shell);
void	expand_tokens(t_token_list *list, t_env_list *env_list);
char	*expand_value(char *raw, t_env_list *env_list);
void	extract_var(char *raw, t_expand_type *exp);
void	expand_var(t_expand_type *exp, t_env_list *env_list);
void	append_exp_str(t_expand_type *exp);

/* Utils */
void	*my_realloc(void *ptr, size_t old_size, size_t new_size);
void	init_exp(t_expand_type *exp, char *raw);
bool	is_valid_var(char *var);
bool	check_subs(char *raw);
void	free_exp(t_expand_type *exp);
char	*error_free(t_expand_type *exp);

#endif