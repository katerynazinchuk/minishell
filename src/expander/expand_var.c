/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:50:25 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/11 17:03:16 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* В парсингу ми маємо перевірити чи існує змінна від експорта (?) */
/* expand в процесі парсинга, щоб ми не розгорнули деліметр */

/* *raw - не оброблені, сирі дані */

//we know we need to expand value
//starts only if we have symbol $ somewhere in line
char	*expand_value(char *raw, t_shell_type *shell)
{
	t_expand_type	exp;

	init_exp(&exp, raw);
	while (raw[i])
	{
		if (raw[exp->i] == '$')
		{
			exp->i++;
			exp->var = extract_var(raw + i, &exp->len_var);
			if (!exp->var)
				return (NULL)//what we need to free?
			exp->str = expand_var(exp->var, exp->len_var, shell);
			append_exp_str(exp);
			//тут треба в exp->res покласти exp->str але д тримаємо в умі що там потрібно переалокувати память за потреби
			exp->i+=exp->len_var;
			//exp->j+=exp->len_var;
		}
		else
			result[exp->j] = raw[exp->i];
		exp->i++;
		exp->j++;
	}
	result[exp->j] = '\0';
	free_exp(exp);
	return (exp->result);
}

//somethinf after $ {} or just var_name
char	*extract_var(char *raw, size_t *len)
{
	if (*raw && *raw == '{' && ft_strchr(raw, '}') != 0)
	{
		*len =(size_t)(raw - ft_strchr(raw, '}') + 1);//щоб урахувати {} бо треба змістити ітератор на всю довжину key_var
		return(ft_strndup(raw + 1, *(len - 1)));//щоб переписати на '\0' останній символ }
	}
	else
	{
		while (*raw && !is_whitespace(*raw))
			(*len)++;
		return(ft_strndup(raw, *(len + 1)));
	}
}

void	append_exp_str(t_expand_type *exp)
{
	size_t	len_str;
	size_t	new_size;
	int		k;

	k = 0;
	len_str = ft_strlen(exp->str);
	if (len_str > exp->len_var)
	{
		new_size = ft_strlen(exp->res) - exp->len_var + len_str;
		exp->res = my_realloc(exp->res, ft_strlen(exp->res), new_size);
		while(k < len_str)
		{
			exp->res[exp->j] = exp->str[k];
			exp->j++;
			k++;
		}
	}
	else 
	{
		
	}
}


