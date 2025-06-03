/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:08:39 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/03 18:05:35 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// структуру exe видалила щоб не тягати по fork

void	executor(t_ast_node *ast, t_shell *shell)
{
	//run_heredoc(&exe, shell)
	run_ast(ast, shell, false);//TODO do we need to keep head_ast in shell to clean ast in case of error
	// Відновили стандартні дескриптори
    // dup2(saved_stdin,  STDIN_FILENO);
    // dup2(saved_stdout, STDOUT_FILENO);
    // close(saved_stdin);
    // close(saved_stdout);
}

void	run_ast(t_ast_node *ast, t_shell *shell, bool in_pipe)
{
	run_cmd(ast, shell);

	//do we need to checl !ast ?
/* 	if (ast->type == AST_PIPE)
		run_pipe(ast, shell);
	else
		run_cmd(ast, shell); */
}

// if (!ast)
// 	return ;

int	run_cmd(t_ast_node *node, t_shell *shell, bool in_pipe)
{
	int	exit_status;
	
	if (!apply_redir(node->redir))
	{
		write(2, "Error redirect\n", 16);
		return (1);
	}
	if (is_builtin(node->value[0]))
	{
		if (in_pipe)
			exit_status = run_fork_builtin(node, shell);
		else
			exit_status = run_builtin(node, shell);
	}
	else
		exit_status = run_external(node, shell);
	return (exit_status);
}


/* int	run_cmd(t_ast_node *node, t_shell *shell, bool in_pipe)
{
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
} */

/* Meooow


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