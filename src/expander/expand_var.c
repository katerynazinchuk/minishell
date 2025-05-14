/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:50:25 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/14 18:39:47 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* В парсингу ми маємо перевірити чи існує змінна від експорта (?) */
/* expand в процесі парсинга, щоб ми не розгорнули деліметр */

/* *raw - не оброблені, сирі дані */

void	expand_tokens(t_token_list *list, t_env_list *env_list)//треба почистити результат від expand_value
{
	t_token	*current;

	current = list->head;
	while(!current)
	{
		if (ft_strchr(current->value, '$'))///start from here
		{
			if (current->q_type != QUOTE_SINGLE)
			{
				if (check_subs(current->value))
					current->bad_subs = 1;
				else
					current->expanded = expand_value(current->value, env_list);
			}
		}
		current = current->next;
	}
}

/* void	*expand_tokens(t_shell_type *shell)//треба почистити результат від expand_value
{
	t_token	*current;

	current = shell->token_list->head;
	while(!current)
	{
		if (ft_strchr(current->value), '$')///start from here
		{
			if (current->q_type != "QUOTE_SINGLE")
			{
				if (check_subs(current->value))
					current->bad_subs = 1;
				else
					current->expanded = expand_value(current->value, shell);
			}
		}
		current->head->next;
	}
} */

bool	check_subs(char *raw)
{
	while (*raw)
	{
		if (*raw && *raw == '{' && *(raw + 1) == '{')
			return (true);
	}
	return (false);
}

//we know we need to expand value
//starts only if we have symbol $ somewhere in line

char	*expand_value(char *raw, t_env_list *env_list)
{
	t_expand_type	exp;

	init_exp(&exp, raw);
	while (raw[exp.i])
	{
		if (raw[exp.i] == '$')
		{
			exp.i++;
			exp.var = extract_var(raw + exp.i, &exp.len_var);
			if (!exp.var)
				return (NULL);//what we need to free?
			exp.str = expand_var(exp.var, exp.len_var, env_list);
			// if (!exp->str)
			// ??
			append_exp_str(&exp);
			exp.i+=exp.len_var;
			exp.j+=ft_strlen(exp.str);
		}
		else
		{
			exp.res[exp.j] = raw[exp.i];
			exp.i++;
		}
		exp.j++;
	}
	exp.res[exp.j] = '\0';
	// free_exp(exp);
	return (exp.res);
}

/* char	*expand_value(char *raw, t_shell_type *shell)
{
	t_expand_type	exp;

	init_exp(&exp, raw);
	while (raw[exp->i])
	{
		if (raw[exp->i] == '$')
		{
			exp->i++;
			exp->var = extract_var(raw + exp->i, &exp->len_var);
			if (!exp->var)
				return (NULL)//what we need to free?
			exp->str = expand_var(exp->var, exp->len_var, shell);
			// if (!exp->str)
			// ??
			append_exp_str(exp);
			exp->i+=exp->len_var;
			//exp->j+=exp->len_var;
		}
		else
			res[exp->j] = raw[exp->i];
		exp->i++;
		exp->j++;
	}
	res[exp->j] = '\0';
	free_exp(exp);
	return (exp->res);
} */

//somethinf after $ {} or just var_name
char	*extract_var(char *raw, size_t *len)
{
	if (*raw == '{' && ft_strchr(raw, '}') != 0)
	{
		*len =(size_t)(raw - ft_strchr(raw, '}') + 1);//щоб урахувати {} бо треба змістити ітератор на всю довжину key_var
		return(ft_strndup(raw + 1, *len - 2));//щоб не забрати останній символ '}'
	}
	else
	{
		while (raw[*len] && !is_whitespace(raw[*len]))
			(*len)++;
		return(ft_strndup(raw, *(len + 1)));
	}
}

void	append_exp_str(t_expand_type *exp)
{
	size_t	len_str;
	size_t	new_size;
	size_t	k;

	k = 0;
	len_str = ft_strlen(exp->str);
	new_size = ft_strlen(exp->res) - exp->len_var + len_str;
	exp->res = my_realloc(exp->res, ft_strlen(exp->res), new_size);
	while(k < len_str)
	{
		exp->res[exp->j] = exp->str[k];
		exp->j++;
		k++;
	}
}

char	*expand_var(char *var, int len, t_env_list *env_list)
{
	t_env_type		*current;
	
	if (is_valid_var(var))
	{
		current = env_list->head;
		while(current)
		{
			if (ft_strncmp(current->key, var, len) == 0)
				return (ft_strdup(current->value));
			current = current->next;
		}
	}
	else if (ft_isdigit(*var))
		return(var + 1);
	// else if (*var == '?')
	// 	return(ft_itoa(shell->last_exit_status));//це алокейт 0-255 чи треба своє писати?
	return (ft_strdup(""));//неіснуюча змінна
}
