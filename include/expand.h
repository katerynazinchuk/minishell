/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:34:24 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/19 21:01:34 by tchernia         ###   ########.fr       */
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

int		expand_segments(t_session *session);
char	*expand_value(char *raw, t_shell *shell);
void	extract_var(char *raw, t_expand_type *exp);
void	expand_var(t_expand_type *exp, t_shell *shell);
void	append_exp_str(t_expand_type *exp);

/* Utils */
void	*my_realloc(void *ptr, size_t old_size, size_t new_size);
void	init_exp(t_expand_type *exp, char *raw);
bool	is_valid_var(char *var);
bool	check_subs(char *raw);
void	free_exp(t_expand_type *exp);
char	*error_free(t_expand_type *exp);
int		is_quote(char c);

#endif