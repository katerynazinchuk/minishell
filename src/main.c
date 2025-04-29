/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:11:01 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/04/29 16:20:20 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* [username@hostname current_working_directory]$ */

//readline return NULL, so (!line) processing case when we use Ctrl+D

int main()
{
	char		*line;
	const char	*prompt = "minishell> ";
	t_token_list	*tokens;

	init_signals();
	while(1)
	{
		//update_prompt(prompt);
		line = readline(prompt);
		if (!line)
		{
			write(1, "exit\n", 4);
			exit (0);
		}
		if(*line)
		{
			tokens = lexer(line);
			if (tokens)
			{
				print_tokens(tokens);
				free_token_list(tokens);
			}
			add_history(line);
		}
		//lexer = init_lexer(line);
		//token = extract_token(lexer, state);
		//parse_tokens(token);
		//execute_command(token);
		// if (*line)
		// 	add_history(line);
		printf("command: %s\n", line);
		free(line);
	}
	return(0);
}
//int argc, char **argv, char **env