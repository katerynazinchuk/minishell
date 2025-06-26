/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:34:24 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/26 13:59:54 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

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

/* -------------------------------------------------------------------------- */

int		expand_segments(t_session *session);
int		process_expansion_loop(char *raw, t_expand_type *exp, \
									t_shell *init_shell);
void	handle_double_dollar_sign(char *raw, t_expand_type *exp);
char	*expand_value(char *raw, t_shell *shell);
int		process_var(char *raw, t_expand_type *exp, t_shell *shell);
void	extract_var(char *raw, t_expand_type *exp);
void	expand_var(t_expand_type *exp, t_shell *shell);
void	append_exp_str(t_expand_type *exp);

/* -------------------------------------------------------------------------- */

void	*my_realloc(void *ptr, size_t old_size, size_t new_size);
int		init_exp(t_expand_type *exp, char *raw);
bool	is_valid_var(char *var);
bool	check_subs(char *raw);
void	free_exp(t_expand_type *exp);
int		error_free(t_expand_type *exp);
int		is_quote(char c);

#endif