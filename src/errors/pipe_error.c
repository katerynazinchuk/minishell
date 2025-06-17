/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:18:42 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/03 15:52:42 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool check_unmached_quotes(char *line)
{
	int i;
	char quote;

	i = 0;
	quote = 0;
	while(line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			if(quote == 0)
				quote = line[i];
			else if (line[i] == quote)
				quote = 0;
		}
		i++;
	}
	if(quote != 0)
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (true);
	}
	return (false);
}
bool last_pipe_error(char *line)
{
	int i;
	i = ft_strlen(line) - 1;
	while (i >= 0 && is_whitespace(line[i]))
		i--;
	if (i >= 0 && line[i] == '|')
		return (true);
	return (false);
}
bool first_pipe_error(char *line)
{
	int i;

	i = 0;
	while (line[i] && is_whitespace(line[i]))
		i++;
	if (line[i] == '|')
	{
		printf("minishell: syntax error: unexpected token `|'\n");
		return (true);
	}
	return (false);
}

char *join_input(char *line)
{
	char *next_line;
	char *joined_line;

	next_line = readline("minishell> ");
	if (!next_line)
	{
		free(line);
		return (NULL);
	}
	joined_line = ft_strjoin(line, next_line);
	free(next_line);
	if (!joined_line)
		return (NULL);
	free(line);
	return (joined_line);
}

char *check_input(char *line)
{
	if(!line)// || ft_strlen(line) == 0)
		return (NULL);//TODO set error
	if (check_unmached_quotes(line))
		return (NULL);//TODO set error
	if (first_pipe_error(line))
		return (NULL);//TODO set error
	if (last_pipe_error(line))
	{
		line = join_input(line);
		if(!line)
			return (NULL);
	}
	return (line);
}

