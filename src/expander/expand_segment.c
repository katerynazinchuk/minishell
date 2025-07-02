/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_segment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:40:38 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/02 13:40:06 by tchernia         ###   ########.fr       */
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
			tmp = expand_seg_value(seg, session->shell);//TODO what if NULL?
			if (!tmp)
				return (handle_expansion_error(seg));
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
	if (ft_strchr(seg->value, '$') && seg->q_type != Q_SINGLE)
	{
		if (check_subs(seg->value))
		{
			check_error(SUBS_ERR, seg->value, GENERAL);
			return (NULL);
		}
		return (expand_value(seg->value, shell));
	}
	return (ft_strdup(seg->value));
}

int	process_expansion_loop(char *raw, t_expand_type *exp, t_shell *init_shell)
{
	while (raw[exp->i])
	{
		if (raw[exp->i] == '$')
		{
			if (raw[exp->i + 1] == '$' || is_whitespace(raw[exp->i + 1]) \
|| raw[exp->i + 1] == '\0')
			{
				handle_double_dollar_sign(raw, exp);
			}
			else
			{
				exp->i++;
				if (process_var(raw, exp, init_shell))
				{
					error_free(exp);
					return (1);
				}
				exp->i += exp->len_var;
				free_exp(exp);
			}
		}
		else
			exp->res[exp->j++] = raw[exp->i++];
	}
	return (0);
}

void	handle_double_dollar_sign(char *raw, t_expand_type *exp)
{
	while (raw[exp->i + 1] && raw[exp->i + 1] == '$')
		exp->res[exp->j++] = raw[exp->i++];
	exp->res[exp->j++] = raw[exp->i++];
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
