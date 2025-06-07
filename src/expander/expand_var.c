/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:50:25 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/05 18:56:40 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* змінна від експорта запишеться в env_list */
/* expand в процесі парсинга, щоб ми не розгорнули деліметр */
/* set flag need to clean - better to change from void to return like write */

bool	expand_segments(t_session *session)//треба почистити результат від expand_value
{
	t_token	*cur;
	t_segment *seg;
	char *tmp;

	cur = session->tokens->head;
	while (cur)
	{
		if(cur->prev && cur->prev->type == T_HEREDOC)
		{
			cur = cur->next;
			continue;
		}
		seg = cur->segment;
		while(seg)
		{
			if (ft_strchr(seg->value, '$') && seg->q_type != Q_SINGLE)///start from here
			{
				if (check_subs(seg->value))
					cur->bad_subs = 1;
				else
					tmp = expand_value(seg->value, session->shell);//TODO what happens if there will be NULL?
			}
			else
				tmp = ft_strdup(seg->value);
			if (!tmp)
				return (false);
			free(seg->value);
			seg->value = tmp;
			seg = seg->next;
		}
		cur = cur->next;
	}
	return (true);
}


/* void	expand_tokens(t_shell *shell)//треба почистити результат від expand_value
{
	t_token	*current;

	current = shell->tokens->head;
	while (current)
	{
		if (ft_strchr(current->value, '$') && current->q_type != Q_SINGLE)///start from here
		{
			if (check_subs(current->value))
				current->bad_subs = 1;
			else
				current->expanded = expand_value(current->value, shell);//TODO what happens if there will be NULL?
		}
		else
			current->expanded = ft_strdup(current->value);
		current = current->next;
	}
} */

char	*expand_value(char *raw, t_shell *shell)
{
	t_expand_type	exp;

	init_exp(&exp, raw);
	while (raw[exp.i])
	{
		if (raw[exp.i] == '$')
		{
			exp.i++;
			extract_var(raw + exp.i, &exp);
			if (!exp.var)
				return (error_free(&exp));
			expand_var(&exp, shell);
			if (!exp.str)
				return (error_free(&exp));
			append_exp_str(&exp);
			if (!exp.res)
				return (error_free(&exp));
			exp.i+=exp.len_var;
			free_exp(&exp);
		}
		else
			exp.res[exp.j++] = raw[exp.i++];
	}
	exp.res[exp.j] = '\0';
	return (exp.res);
}

//somethinf after $ {} or just var_name
void	extract_var(char *raw, t_expand_type *exp)
{
	exp->len_var = 0;
	if (*raw == '{' && ft_strchr(raw, '}') != 0)
	{
		exp->len_var = (size_t)(ft_strchr(raw, '}') - raw + 1);// + 1 щоб урахувати {}
		exp->var = ft_strndup(raw + 1, exp->len_var - 2);// - 2 щоб не забрати останній символ '}'
	}
	else
	{
		while (raw[exp->len_var] && !is_whitespace(raw[exp->len_var])
			&& !is_quote(raw[exp->len_var]))
			exp->len_var++;
		exp->var = ft_strndup(raw, exp->len_var);
	}
}

void	expand_var(t_expand_type *exp, t_shell *shell)
{
	char	*tmp;

	if (is_valid_var(exp->var))
	{
		if (!get_env_value(exp->var, shell->env_list, &tmp))
			return ;
		exp->str = ft_strdup(tmp);
	}
	else if (ft_isdigit(*exp->var))
		exp->str = ft_strdup(exp->var + 1);
	else if (*exp->var == '?')
		exp->str = ft_itoa(shell->last_exit_status);//TODO do we need to expand not only with echo ?
	else
		exp->str = ft_strdup("");//неіснуюча змінна
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
	while (k < len_str)
	{
		exp->res[exp->j] = exp->str[k];
		exp->j++;
		k++;
	}
	exp->res[exp->j] = '\0';
}
