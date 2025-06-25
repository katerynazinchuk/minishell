/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:50:25 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/25 17:26:18 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_var(char *raw, t_expand_type *exp, t_shell *shell);

int	expand_segments(t_session *session)
{
	t_token		*cur;
	t_segment	*seg;
	char		*tmp;

	cur = session->tokens->head;
	while (cur)
	{
		if (cur->prev && cur->prev->type == T_HEREDOC)
		{
			cur = cur->next;
			continue ;
		}
		seg = cur->segment;
		while (seg)
		{
			if (ft_strchr(seg->value, '$') && seg->q_type != Q_SINGLE)
			{
				if (check_subs(seg->value))
					return (check_error(BAD_SUBS, seg->value, GENERAL));
				else
					tmp = expand_value(seg->value, session->shell);//TODO what happens if there will be NULL?
			}
			else
				tmp = ft_strdup(seg->value);
			if (!tmp)
			{
				free(seg->value);
				return (check_error(ENOMEM, "create tokens: ", GENERAL));
			}
			free(seg->value);
			seg->value = tmp;
			seg = seg->next;
		}
		cur = cur->next;
	}
	return (0);
}

char	*expand_value(char *raw, t_shell *shell)
{
	t_expand_type	exp;

	if (init_exp(&exp, raw))
		return (NULL);
	while (raw[exp.i])
	{
		if (raw[exp.i] == '$')
		{
			if (raw[exp.i + 1] == '$' || is_whitespace(raw[exp.i + 1]) \
				|| raw[exp.i + 1] == '\0')
			{
				while (raw[exp.i + 1] && raw[exp.i + 1] == '$')
					exp.res[exp.j++] = raw[exp.i++];
				exp.res[exp.j++] = raw[exp.i++];
			}
			else
			{
				exp.i++;
				if (process_var(raw, &exp, shell))
				{
					error_free(&exp);
					return (NULL);
				}
				exp.i += exp.len_var;
				free_exp(&exp);
			}
		}
		else
			exp.res[exp.j++] = raw[exp.i++];
	}
	exp.res[exp.j] = '\0';
	return (exp.res);
}

static int	process_var(char *raw, t_expand_type *exp, t_shell *shell)
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
		{
			exp->str = ft_strdup(tmp);
			if (!exp->str)
				exp->str = NULL;
		}
	}
	else if (ft_isdigit(*exp->var))
		exp->str = ft_strdup(exp->var + 1);
	else if (*exp->var == '?')
		exp->str = ft_itoa(shell->status);
	else
		exp->str = ft_strdup("");
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
