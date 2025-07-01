/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:06:57 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/01 12:23:23 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env_list *env_list);
int		is_valid_input(char *var);

int	builtin_export(char **argv, t_env_list *env_list)
{
	int		i;
	char	*divider;
	char	*key;
	char	*value;

	(void)env_list;
	i = 1;
	if (!argv[1])
		print_export(env_list);
	while (argv[i])
	{
		if (!is_valid_input(argv[i]))
			return (check_error(EXPORT_ERR, argv[i], GENERAL));
		else
		{
			divider = ft_strchr(argv[i], '=');
			if (divider)
			{
				key = ft_substr(argv[i], 0, divider - argv[i]);
				value = ft_strdup(divider + 1);
				if (!key || !value || set_env(env_list, key, value))
					return (ENOMEM);
				free(key);
				free(value);
			}
			else
				set_env(env_list, argv[i], NULL);
		}
		i++;
	}
	return (0);
}

void	print_export(t_env_list *env_list)
{
	t_env_type	*current;

	current = env_list->head;
	while (current)
	{
		if (current->key && current->value)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(current->value, 1);
			ft_putstr_fd("\"", 1);
			write(1, "\n", 1);
		}
		else if (current->key && !current->value)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(current->key, 1);
			write(1, "\n", 1);
		}
		current = current->next;
	}
}

int	is_valid_input(char *var)
{
	int	i;

	i = 1;
	if (!var || !var[0] || ft_isdigit(var[0]) || \
(!ft_isalpha(var[0]) && var[0] == '_') || var[0] == '=')
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
			return (0);
		i++;
	}
	return (1);
}
