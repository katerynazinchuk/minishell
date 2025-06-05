/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:37:53 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/05 15:41:55 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <fcntl.h>
# include <linux/limits.h>

// typedef struct s_execute
// {
// // 	// t_shell		*shell;
// 	// t_ast_node	*ast;
// 	int			fd[2];
// 	// int			prev_fd;
// 	// t_list		*pid_list;
// 	// t_list		*heredoc_fds;
// }	t_execute;

typedef struct s_cmd_info
{
	char				**argv;            // command + arguments
	char				*infile;           // for `<`
	char				*outfile;          // for `>` or `>>`
	int					append_mode;        // 1 if >>, 0 if >
	int					is_heredoc;         // 1 if heredoc, 0 otherwise
	char				*heredoc_delim;    // heredoc delimiter
	struct s_command	*next; // next in pipe chain
}	t_cmd_info;

typedef bool	(*t_redir_handler)(t_redir *redir_list);
/* typedef int		(*t_builtin_fn)(char **argv, t_env_list *env_list);

typedef struct s_builtin
{
	char			*name;
	t_builtin_fn	func;
}	t_builtin; */

/*____________________________________________________________________________*/
void	executor(t_ast_node *ast, t_shell *shell);
// void	run_ast(t_ast_node *ast_node, t_shell *shell);
// void	run_cmd(t_ast_node *node, t_shell *shell);

// void	run_builtin(t_ast_node *node, t_shell *shell);

void	run_external(t_ast_node *node, t_shell *shell);

bool	apply_redir(t_redir *redir_list);


/* ___________________________________________________________________________*/

void	run_ast(t_ast_node *ast, t_shell *shell);
int		run_cmd(t_ast_node *node, t_shell *shell);
char	**env_to_arr(t_env_list *env_list);
char	*find_path(char *cmd, t_env_list *env_list, int error_code);
void	free_arr(char **arr);

#endif