#include "minishell.h"

/* [username@hostname current_working_directory]$ */

//readline return NULL, so (!line) processing case when we use Ctrl+D

int main()
{
	char		*line;
	const char	*prompt = "minishell> ";

	init_signals();
	while(1)
	{
		//update_prompt(prompt);
		line = readline(prompt);
		if (!line)
		{
			write(1, "exit\n", 6);
			exit (0);
		}
		// if (*line)
		// 	add_history(line);
		printf("command: %s\n", line);
		free(line);
	}
	return(0);
}
//int argc, char **argv, char **env