/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:08:39 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/30 13:30:26 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* typedef struct	s_ast_node
{
	t_ast_type			type; 
	char				**value;//command
	t_redir				*redir;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node; */

void	executor(t_ast_node *ast, t_shell *shell)
{
	// t_execute	exe;

	// init_execute(&exe);
	//run_heredoc(&exe, shell)
	run_ast(ast, shell);//TODO do we need to keep head_ast in shell to clean ast in case of error
	// Відновили стандартні дескриптори
    // dup2(saved_stdin,  STDIN_FILENO);
    // dup2(saved_stdout, STDOUT_FILENO);
    // close(saved_stdin);
    // close(saved_stdout);
}

void	run_ast(t_ast_node *ast, t_shell *shell)
{
	(void)shell;
	// write(1, "1\n", 2);
	if (!ast)
		return ;
	if (ast->type == AST_COMMAND)
		// printf("HELLO\n");
		 run_cmd(ast, shell);
	// if (ast->type == AST_PIPE)
	// {
	// 	run_ast(ast->left, shell, exe);
	// 	run_ast(ast->right, shell, exe);
	// }
	// else
	// {
	// 	run_cmd(ast, shell, exe);
	// }
}

int	run_cmd(t_ast_node *node, t_shell *shell)
{
	// t_cmd_info	cmd_info;

	// init_cmd_info(&cmd_info, exe);
	// if (validate_redir(node->redir))
	// 	printf("Valide redirections \n");
	// else 
	// 	printf("Not valide redirections \n");
	// //init_cmd_info
	// if (is_builtin(&cmd_info, shell, exe))
	// 	run_builtin(&cmd_info, shell, exe);
	// else
	// 	run_external(&cmd_info, shell, exe);

	pid_t	proc_id;
	char	**env_arr;
	int	status = 0;

	proc_id = fork();
	if (proc_id == 0)
	{
		env_arr = env_to_arr(shell->env_list);
		if (!env_arr)
			exit(1);
		execve (node->value[0], node->value, env_arr);
		//clean all structs from upper levels
		exit(1);
	}
	waitpid(proc_id, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}


/* Meooow

bool applay_in(t_redir *red)
{
	int fd;

	fd = open(redir->connection, O_RDONLY);
	if (fd < 0)
		return (false);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (true);
}

bool applay_out(t_redir *red)
{
	fd = open(redir->connection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (false);//TODO do we need to close fd in this case?
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (true);
}

bool applay_append(t_redir *red)
{
	fd = open(redir->connection, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (false);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return(true);
}

bool apply_red(t_redir *head)
{
	static t_redir_handler redmap[] = {
		applay_in,
		applay_out,
		applay_append,
		NULL
	};

	while (head)
	{
		if (redmap[red->type](head) == false)
			return (false);
		head = head->next;
	}
	return (true);
}

int exe_cmd(t_ast_node *node, t_shell *shell)
{
	pid_t pid;
	int status;
	char **args;
	
	args = node->value;
	pid = fork();
	if (pid = 0)
	{
		if(apply_red(node->redir) == false) 
			exit(1);
		
		execve(args[0], args, shel);
		if (errno == ENOENT)
		{
			"cmd: command not found";
			exit(126);
		}
		exit(1);
	}
	waitpid(pid, &status, 0);
	return(128 + SIGNAL or STATUS);
}
typedef bool	(*t_buildin_fn)(t_ast_node *node, t_shell *shell);

int exe_buildin(t_ast_node *node, t_shell *shell)
{
	static t_buildin_fn fnmap[5];
	static char* strmap[5] = {"echo", "pwd", "export", "exit", NULL}
	int i;

	i = 0;
	while (strmap[i])
	{
		if (ft_strncmp(node->value[0], strmap[i], ft_strlen(strmap[i])) == 0)
			break ;
		i++;
	}
	if (i < 5)
		fnmap[i](node, shell);
	else
		exe_cmd(node, shell);
}

int exe_pipe(t_ast_node *node, t_shell *shell)
{
	pid_t pid1;
	pid_t pid2;
	int status;
	int pipefd[2];

	pipe(pipefd);

	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(exe(node->left));
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(exe(node->right));
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0)
	if (SIGNAL)
		return (128 + SIGNAL);
	return (STATUS)
}

int exe(t_ast_node *node, t_shell *shell)
{
	if (node->type == AST_PIPE)
		exe_pipe(node, shell);
	else if (node->type == AST_COMMAND)
		exe_buildin(t_ast_node *node, t_shell *shell);
	else
		exit(1);
} */