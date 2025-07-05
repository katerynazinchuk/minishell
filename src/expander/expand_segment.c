/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_segment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:40:38 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/05 14:08:49 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			tmp = expand_seg_value(seg, session->shell);
			if (!tmp)
				return (1);
			free(seg->value);
			seg->value = tmp;
			seg = seg->next;
		}
		cur = cur->next;
	}
	return (0);
}

char	*expand_seg_value(t_segment *seg, t_shell *shell)
{
	char	*res;

	if (ft_strchr(seg->value, '$') && seg->q_type != Q_SINGLE)
	{
		if (check_subs(seg->value))
		{
			check_error(SUBS_ERR, seg->value, GENERAL);
			return (NULL);
		}
		return (expand_value(seg->value, shell));
	}
	res = ft_strdup(seg->value);
	if (!res)
	{
		check_error(ENOMEM, NULL, GENERAL);
		return (NULL);
	}
	return (res);
}

char	*expand_value(char *raw, t_shell *shell)
{
	t_expand_type	exp;

	if (init_exp(&exp, raw))
		return (NULL);
	if (process_expansion_loop(raw, &exp, shell))
	{
		error_free(&exp);
		return (NULL);
	}
	exp.res[exp.j] = '\0';
	return (exp.res);
}

int	process_expansion_loop(char *raw, t_expand_type *exp, t_shell *shell)
{
	while (raw[exp->i])
	{
		if (raw[exp->i] == '$' && raw[exp->i + 1] != '\0')
		{
			if (check_expand_case(raw[exp->i +1]))
			{
				if (handle_variable_exp(raw, exp, shell))
					return (1);
			}
			else
				exp->res[exp->j++] = raw[exp->i++];
		}
		else
			exp->res[exp->j++] = raw[exp->i++];
	}
	return (0);
}

int	handle_variable_exp(char *raw, t_expand_type *exp, t_shell *shell)
{
	exp->i++;
	if (process_var(raw, exp, shell))
	{
		error_free(exp);
		return (1);
	}
	exp->i += exp->len_var;
	free_exp(exp);
	return (0);
}
