/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:34:24 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/11 17:07:28 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
#define EXPAND_H

typedef struct s_expand
{
	size_t	len_var;
	char	*res;
	char	*var;
	char	*str;
	int		j;
	int		i;
}	t_expand_type;

char	*expand_value(char *raw, t_shell_type *shell);
void	*my_realloc(void *ptr, size_t old_size, size_t new_size);
char	*extract_var(char *raw, size_t *len);
void	init_exp(t_expand_type *exp, char *raw);
bool	is_valid_var(char *var);

#endif