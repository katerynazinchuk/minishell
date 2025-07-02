/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:06:57 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/02 13:47:31 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env_list *env_list);
int		is_valid_input(char *var);

static int	add_to_env(char *arg, t_env_list *env_list)
{	
	char	*divider;
	char	*key;
	char	*value;

	divider = ft_strchr(arg, '=');
	if (!divider)
		return (1);
	key = ft_substr(arg, 0, divider - arg);
	value = ft_strdup(divider + 1);
	if (!key || !value || set_env(env_list, key, value))
	{
		free(key);
		free(value);
		return (check_error(ENOMEM, NULL, GENERAL));
	}
	free(key);
	free(value);
	return (0);	
}

static int	no_args(char **argv, t_env_list *env_list)
{
	if (!argv[1])
	{
		print_export(env_list);
		return (1);
	}
	else
		return (0);
}

int	builtin_export(char **argv, t_env_list *env_list)
{
	int		i;

	(void)env_list;
	i = 0;
	if (no_args(argv, env_list))
		return (0);
	while (argv[++i])
	{
		if (!is_valid_input(argv[i]))
			return (check_error(EXPORT_ERR, argv[i], GENERAL));
		else
		{
			if(ft_strchr(argv[i], '='))
			{
				if (add_to_env(argv[i], env_list))
					return (1);
			}
			else
			{
				if (set_env(env_list, argv[i], NULL))
					return (1);
			}
		}
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
