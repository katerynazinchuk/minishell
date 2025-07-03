/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:18:42 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/03 17:39:13 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_unmached_quotes(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			if (quote == 0)
				quote = line[i];
			else if (line[i] == quote)
				quote = 0;
		}
		i++;
	}
	if (quote != 0)
		return (check_error(SYNTAX_ERR, "unclosed quote", GENERAL));
	return (false);
}

bool	last_pipe_error(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i >= 0 && is_whitespace(line[i]))
		i--;
	if (i >= 0 && line[i] == '|')
		return (check_error(SYNTAX_ERR, "near unexpected token `|'", GENERAL));
	return (false);
}

bool	first_pipe_error(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_whitespace(line[i]))
		i++;
	if (line[i] == '|')
		return (check_error(SYNTAX_ERR, "near unexpected token `|'", GENERAL));
	return (false);
}

int	check_input(char *line, t_session *session)
{
	session->line = line;
	if (!line)
		return (1);
	if (check_unmached_quotes(line))
		return (2);
	if (first_pipe_error(line))
		return (2);
	if (last_pipe_error(line))
		return (2);
	return (0);
}
