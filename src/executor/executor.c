/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:08:39 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/20 12:20:17 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_session *session)
{
	session->shell->status = run_ast(session->ast, session);
	restore_fd(session);
}


int	run_ast(t_ast_node *ast, t_session *session)
{
	if (!ast)
		return (0);
	if (ast->type == AST_PIPE)
		return(run_pipe(ast, session));
	else
		return(run_cmd(ast, session));
}

int	run_cmd(t_ast_node *node, t_session *session)
{
	t_builtin_fn	builtin_fn;
	
	if (apply_redir(node->redir))
		return (1);
	// {
	// 	write(2, "Error redirect\n", 16);
	// 	return (1);
	// }
	if (!node->value[0])
		return (0);
	builtin_fn = get_builtin_fn(node->value[0]);
	if (builtin_fn)
		session->shell->status = builtin_fn(node->value, session->shell->env_list);
	else
		session->shell->status = run_external(node, session);
	return (session->shell->status);
}

int	run_pipe(t_ast_node *ast, t_session *session)
{
	pid_t	id_left;
	pid_t	id_right;
	int		status;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		write(2, "Pipe error \n", 13);
	//pipe_error();
	id_left = child_left(ast->left, session, pipe_fd);
	if (id_left < 0)
	{
		free_in_fork(session, NULL);
		return (1);
	}
	id_right = child_right(ast->right, session, pipe_fd);
	if (id_right < 0)
	{
		free_in_fork(session, NULL);
		waitpid(id_left, NULL, 0);//?
		//ft_fail_child("fork", pipe_fd); return
	}
	close_pipe_fd(pipe_fd);
	waitpid(id_left, NULL, 0);
	waitpid(id_right, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}


pid_t	child_left(t_ast_node *node, t_session *session, int *pipe_fd)
{
	pid_t	proc_id;
	int		exit_status;

	proc_id = fork();
	if (proc_id < 0)
	{
		close_pipe_fd(pipe_fd);
		return (-1);
	}
	else if(proc_id == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close_pipe_fd(pipe_fd);
		exit_status = run_ast(node, session);
		free_in_fork(session, NULL);
		exit(exit_status);//or return ?
	}
	return (proc_id);
}

pid_t	child_right(t_ast_node *node, t_session *session, int *pipe_fd)
{
	pid_t	proc_id;
	int		exit_status;


	proc_id = fork();
	if (proc_id < 0)
	{
		close_pipe_fd(pipe_fd);
		return (-1);
	}
	else if(proc_id == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close_pipe_fd(pipe_fd);
		exit_status = run_cmd(node, session);
		free_env_list(session->shell->env_list);
		free_ast(&session->ast);
		exit(exit_status);//or return ?
	}
	return (proc_id);
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