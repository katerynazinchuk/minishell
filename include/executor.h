/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:37:53 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/29 17:00:47 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <fcntl.h>

typedef struct s_execute
{
	// t_shell		*shell;
	// t_ast_node	*ast;
	int			fd[2];
	// int			prev_fd;
	// t_list		*pid_list;
	// t_list		*heredoc_fds;
}	t_execute;

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

/*____________________________________________________________________________*/
void	executor(t_ast_node *ast, t_shell *shell);
void	init_execute(t_execute *exe);
// void	run_ast(t_ast_node *ast_node, t_shell *shell, t_execute *exe);
// void	run_cmd(t_ast_node *node, t_shell *shell, t_execute *exe);
void	run_builtin(t_cmd_info *cmd_info, t_shell *shell, t_execute *exe);
void	run_external(t_cmd_info *cmd_info, t_shell *shell, t_execute *exe);
void	init_cmd_info(t_cmd_info *cmd_info, t_execute *exe);
bool	validate_redir(t_redir *redir_list);
bool	is_builtin(t_cmd_info *cmd_info, t_shell *shell, t_execute *exe);

/* ___________________________________________________________________________*/

int		run_cmd(t_ast_node *node, t_shell *shell);
void	run_ast(t_ast_node *ast, t_shell *shell);
char	**env_to_arr(t_env_list *env_list);

#endif