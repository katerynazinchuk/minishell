/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:18:42 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/22 18:04:03 by tchernia         ###   ########.fr       */
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
		return (check_error(SYNTAX_ERROR, "unclosed quote", GENERAL));
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
		return (check_error(SYNTAX_ERROR, "unexpected token `|'", GENERAL));

	return (false);
}

char *join_input(char *line, int *flag, t_shell *shell)
{
	char *next_line;
	char *joined_line;
	(void)flag;
	(void)shell;

	// setsignal(HEREDOC_SIG);
	// rl_event_hook = event_handler;
	next_line = readline("pipe> ");
	if (!next_line)
	{
		free(line);
		check_error(ENOMEM, NULL, GENERAL);//TODO track this
		return (NULL);
	}
	// if (g_signal != 0)
	// {
	// 	add_history(line);
	// 	shell->status = 128 + g_signal;
	// 	setsignal(MAIN_SIG);
	// 	free(line);
	// 	*flag = 1;
	// 	return (NULL);
	// }
	joined_line = ft_strjoin(line, next_line);
	free(next_line);
	if (!joined_line)
	{
		check_error(ENOMEM, "Create line", GENERAL);
		return (NULL);
	}
	free(line);
	return (joined_line);
}

int	check_input(char *line, t_session *session)
{
	int	flag;

	if(!line)
		return (1);
	if (check_unmached_quotes(line))
		return (2);
	if (first_pipe_error(line))
		return (2);
	flag = 0;
	if (last_pipe_error(line))
	{
		line = join_input(line, &flag, session->shell);
		if (!line && flag)
			return (2);
		if(!line)
			return (check_error(ENOMEM, "Join fail", GENERAL));
	}
	session->line = line;
	return (0);
}

/* char *check_input(char *line)
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
} */
