/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:50:25 by tchernia          #+#    #+#             */
/*   Updated: 2025/07/05 14:01:07 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_var(char *raw, t_expand_type *exp, t_shell *shell)
{
	extract_var(raw + exp->i, exp);
	if (!exp->var)
		return (error_free(exp));
	expand_var(exp, shell);
	if (!exp->str)
		return (error_free(exp));
	append_exp_str(exp);
	if (!exp->res)
		return (error_free(exp));
	return (0);
}

void	extract_var(char *raw, t_expand_type *exp)
{
	exp->len_var = 0;
	if (*raw == '{' && ft_strchr(raw, '}') != 0)
	{
		exp->len_var = (size_t)(ft_strchr(raw, '}') - raw + 1);
		exp->var = ft_strndup(raw + 1, exp->len_var - 2);
	}
	else if (raw[exp->len_var] == '?')
	{
		exp->len_var = 1;
		exp->var = ft_strndup(raw, exp->len_var);
	}
	else
	{
		while (raw[exp->len_var] && !is_whitespace(raw[exp->len_var])
			&& !is_quote(raw[exp->len_var]) && raw[exp->len_var] != '$')
			exp->len_var++;
		exp->var = ft_strndup(raw, exp->len_var);
	}
	if (!exp->var)
		check_error(ENOMEM, "expand variable", GENERAL);
}

void	expand_var(t_expand_type *exp, t_shell *shell)
{
	int		flag;
	char	*tmp;

	if (is_valid_var(exp->var))
	{
		flag = get_env_value(exp->var, shell->env_list, &tmp);
		if (!flag)
			exp->str = ft_strdup("");
		else
			exp->str = ft_strdup(tmp);
	}
	else if (ft_isdigit(*exp->var))
		exp->str = ft_strdup(exp->var + 1);
	else if (*exp->var == '?')
		exp->str = ft_itoa(shell->status);
	else
		exp->str = ft_strdup("");
	if (!exp->str)
		check_error(ENOMEM, "expand variable", GENERAL);
}

void	append_exp_str(t_expand_type *exp)
{
	size_t	len_str;
	size_t	new_size;
	size_t	k;

	k = 0;
	len_str = ft_strlen(exp->str);
	new_size = exp->j + ft_strlen(exp->str) + (exp->len_raw - exp->i) + 1;
	exp->res = my_realloc(exp->res, ft_strlen(exp->res), new_size);
	if (!exp->res)
		return ;
	while (k < len_str)
	{
		exp->res[exp->j] = exp->str[k];
		exp->j++;
		k++;
	}
	exp->res[exp->j] = '\0';
}

bool	is_valid_var(char *var)
{
	if (ft_isalpha(*var) || *var == '_')
		return (true);
	return (false);
}
