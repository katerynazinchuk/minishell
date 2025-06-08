/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_external.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:59:32 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/08 13:24:43 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_external(t_ast_node *node, t_shell *shell)
{
	pid_t	proc_id;
	int		exit_status;
	char	**env_arr;

	exit_status = 0;
	proc_id = fork();
	if (proc_id < 0)
		return (1);//TODO check return
	if (proc_id == 0)
	{
		env_arr = env_to_arr(shell->env_list); //can be NULL
		if (!env_arr)
		{
			free_env_list(shell->env_list);
			//free_ast till it exist ? from head till NULL
			exit (1);
		}
		if (!find_path(node->value, shell->env_list))
		{
			free_arr(env_arr);
			free_env_list(shell->env_list);
			//free_ast
			errno = ENOMEM;
			perror("minishell executor ");
			exit(1);
			
		}
		if(execve(node->value[0], node->value, env_arr) == -1)
		{
			if (errno == ENOENT)
			{
				ft_putstr_fd(node->value[0], 2);
				ft_putstr_fd(": command not found\n", 2);
				exit_status = 127;
			}
			free_arr(env_arr);
			free_env_list(shell->env_list);
			exit (exit_status);
		}
		exit(1);
	}
	waitpid(proc_id, &exit_status, 0);
	if (WIFSIGNALED(exit_status))
		return(128 + WTERMSIG(exit_status));
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return(1);
}

//execve will return ENOENT and we need to change it to " : command not found"

//8/06/2025 13/24

/* ➜  4_Minishell git:(executor_tetiana) ✗ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp ./minishell

==70607== Memcheck, a memory error detector
==70607== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==70607== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==70607== Command: ./minishell
==70607== 
tchernia:~$ njknln;
AST_COMMAND: [njknln;] 
njknln;: command not found
==70624== 
==70624== HEAP SUMMARY:
==70624==     in use at exit: 208,291 bytes in 228 blocks
==70624==   total heap usage: 771 allocs, 543 frees, 246,859 bytes allocated
==70624== 
==70624== 8 bytes in 1 blocks are still reachable in loss record 3 of 69
==70624==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==70624==    by 0x405864: ft_strdup (ft_strdup.c:20)
==70624==    by 0x403A78: tokens_to_argv (parser.c:123)
==70624==    by 0x403911: parse_command (parser.c:48)
==70624==    by 0x403C5E: parse_pipe (parser.c:100)
==70624==    by 0x4053F2: parser (main.c:101)
==70624==    by 0x405334: process_line (main.c:83)
==70624==    by 0x4052DD: run_shell (main.c:69)
==70624==    by 0x405242: main (main.c:44)
==70624== 
==70624== 16 bytes in 1 blocks are still reachable in loss record 13 of 69
==70624==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==70624==    by 0x4039FA: tokens_to_argv (parser.c:116)
==70624==    by 0x403911: parse_command (parser.c:48)
==70624==    by 0x403C5E: parse_pipe (parser.c:100)
==70624==    by 0x4053F2: parser (main.c:101)
==70624==    by 0x405334: process_line (main.c:83)
==70624==    by 0x4052DD: run_shell (main.c:69)
==70624==    by 0x405242: main (main.c:44)
==70624== 
==70624== 40 bytes in 1 blocks are still reachable in loss record 18 of 69
==70624==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==70624==    by 0x403838: create_ast_node (parser.c:19)
==70624==    by 0x4038A5: parse_command (parser.c:36)
==70624==    by 0x403C5E: parse_pipe (parser.c:100)
==70624==    by 0x4053F2: parser (main.c:101)
==70624==    by 0x405334: process_line (main.c:83)
==70624==    by 0x4052DD: run_shell (main.c:69)
==70624==    by 0x405242: main (main.c:44)
==70624== 
==70624== LEAK SUMMARY:
==70624==    definitely lost: 0 bytes in 0 blocks
==70624==    indirectly lost: 0 bytes in 0 blocks
==70624==      possibly lost: 0 bytes in 0 blocks
==70624==    still reachable: 64 bytes in 3 blocks
==70624==         suppressed: 208,227 bytes in 225 blocks
==70624== 
==70624== For lists of detected and suppressed errors, rerun with: -s
==70624== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
 */