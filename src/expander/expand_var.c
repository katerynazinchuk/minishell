/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:50:25 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/07 17:24:32 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* В парсингу ми маємо перевірити чи існує змінна від експорта (?) */

/* *raw - не оброблені, сирі дані */



void	*expand_tokens(t_shell_type *shell)
{
	t_token_type	*current;

	current = shell->token_list->head;
	while(!current)
	{
		if (ft_strchr(current->value), '$')///start from here
		{
			if (current->q_type != "QUOTE_SINGLE")
				{
					update_value(current->value, shell->env_list);
				}
		}
		current->head->next;
	}
}

//we know we need to expand value
//starts only if we have symbol $ somewhere in line
char	*expand_value(char *raw, t_shell_type *shell)
{
	char	*str;
	int		i;
	int		j;

	str = ft_calloc(ft_strlen(raw) + 1, sizeof(char));
	i = 0;
	while (raw[i])
	{
		if (raw[i] == '$')
		{
			if (raw[i + 1] && raw[i + 1] == '{' &&
				ft_strchr(raw + i + 2, '}') != 0)
			{
				extract_var(raw + i + 1, i + 1)
				//cut {} str
				//is_valid_var()
				//expand_var
			}
			else
			{
				//is_valid_var
				expand_var(raw + 1);
			}
			parse_var(raw[i], shell);
		}
		i++;
	}
}

char	*extract_var(char *raw, int i)
{
	return();
}
	
	while (*str)
	{
		if (ft_strchr(str, '$') != 0)
		{
			if (*(str + 1) == '{' && ft_strchr(str + 2, '}') != 0)
			{
				//cut {} str
				//is_valid_var()
				//expand_var
			}
			else
			{
				//is_valid_var
				expand_var(str+1);
			}
		}
		str++;
	}
if (ft_strchr(str, '{') != 0 && ft_strrchr(str, '}') != 0)
{
	str = 
	
}
if (*(ft_strchr(str, '$') + 1) == '_' ||
	ft_isalpha(*(ft_strchr(str, '$') + 1)))
	
