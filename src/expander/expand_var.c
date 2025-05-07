/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:50:25 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/07 19:09:51 by tchernia         ###   ########.fr       */
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
	char	*result;
	char	*var;
	int		len;
	int		i;
	int		j;

	result = ft_calloc(ft_strlen(raw) + 1, sizeof(char));
	if (!result)
		return (NULL)//what we need to free ?
	i = 0;
	j = 0;
	while (raw[i])
	{
		if (raw[i] == '$')
		{
			i++;
			var = extract_var(raw + i, &len);
			if (!var)
				return (NULL)//what we need to free?
			if (is_valid_var(var))
				//expand_var
			else
				//тут ще кейс коли число то треба першу цифру скинути

				
/* 			if (raw[i] && raw[i] == '{' && ft_strchr(raw + i, '}') != 0)
			{
				extract_var(raw + i)
				expand_var()
				//cut {} str
				//is_valid_var()
			}
			else
			{
				//is_valid_var
				expand_var(raw + 1);
			}
			parse_var(raw[i], shell); */
		}
		else
			result[j] = raw[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

//somethinf after $ {} or just var_name
char	*extract_var(char *raw, int *len)
{
	len = 0;
	if (*raw && *raw == '{' && ft_strchr(raw, '}') != 0)
	{
		len = raw - ft_strchr(raw, '}') + 1;//щоб урахувати {} бо треба змістити ітератор на всю довжину key_var
		return(ft_strndup(raw + 1, len));//щоб переписати на '\0' останній символ }
	}
	else
	{
		while (*raw && !is_whitespace(*raw))
			len++;
		return(ft_strndup(raw, len + 1));
	}
}

bool	is_valid_var(char *var)
{
	if (ft_isalpha(*var) || *var == '_')
		return (true);
	return (false);
}



/* 	else if (*raw && (ft_isalpha(raw) || *raw == '_'))
	{
		while (*raw && !is_whitespace(*raw))
			len++;
		return(ft_strndup(raw, len + 1));
	}
	else
		return(ft_strndup());

 */


	
/* 	int	i;
	int	len;

	i = 0;
	while (raw[i])
	{
		if (raw[i] && raw[i] == '{' && ft_strchr(raw + i, '}') != 0)
		
	}
		
	len = raw - ft_strchr(raw, '}');
	return(ft_strndup(raw, len + 1));
 */
	
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
	



