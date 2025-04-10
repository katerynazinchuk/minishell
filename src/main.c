#include "minishell.h"

int main()
{
	char		*line;
	const char	*prompt = "minishell> ";

	while(1)
	{
		line = readline(prompt);
		if (!line)
		{
			ft_putendl_fd("error", 2);
			exit (1);
		}
		// if (*line)
		// 	add_history(line);
		printf("command: %s\n", line);
		free(line);
	}
	return(0);
}
//int argc, char **argv, char **env