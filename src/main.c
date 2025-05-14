/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:11:01 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/14 18:38:14 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_list(t_env_list *env_list);


/* [username@hostname current_working_directory]$ */

//readline return NULL, so (!line) processing case when we use Ctrl+D

int main(int argc, char **argv, char **env)
{
	char		*line;
	const char	*prompt = "minishell> ";
	t_token_list	*tokens;
	t_env_list		*env_list;
	
	(void)argc;
	(void)argv;
	// init_signals();
	env_list = fill_env_list(env);
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
			// print_env_list(env_list);
			tokens = fill_tokens(line);
			if (tokens)
			{
				print_tokens(tokens, env_list);
				free_token_list(tokens);
			}
			add_history(line);
		}
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
void	print_env_list(t_env_list *env_list)
{
	t_env_type	*current;
	
	current = env_list->head;
	while (current)
	{
		printf("key: %s\n value: %s\n\n", current->key, current->value);
		current = current->next;
	}
}
