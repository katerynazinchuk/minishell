/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:37:53 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/20 12:20:40 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <fcntl.h>
# include <linux/limits.h>


typedef bool	(*t_redir_handler)(t_redir *redir_list);
typedef int		(*t_builtin_fn)(char **argv, t_env_list *env_list);

typedef struct s_builtin
{
	char			*name;
	t_builtin_fn	func;
}	t_builtin;

/*____________________________________________________________________________*/
void			executor(t_session	*session);
int				run_ast(t_ast_node *ast, t_session *session);
int				run_pipe(t_ast_node *ast, t_session *session);
pid_t			child_left(t_ast_node *node, t_session *session, int *pipe_fd);
pid_t			child_right(t_ast_node *node, t_session *session, int *pipe_fd);
int				run_cmd(t_ast_node *node, t_session *session);
int			apply_redir(t_redir *redir_list);
int				run_external(t_ast_node *node, t_session *session);
t_builtin_fn	get_builtin_fn(char *cmd);

/* ___________________________________________________________________________*/
/* Utils */
/* ___________________________________________________________________________*/

char	**env_to_arr(t_env_list *env_list);
int		find_path(char **value, t_env_list *env_list);
void	free_arr(char **arr);
void	close_pipe_fd(int *pipe_fd);
void	restore_fd(t_session *session);
void	free_in_fork(t_session *session, char **env_arr);
bool	is_new_line(char *str);

/* Builtin */
int		builtin_echo(char **argv, t_env_list *env_list);
int		builtin_cd(char **argv, t_env_list *env_list);
int		builtin_pwd(char **argv, t_env_list *env_list);
int		builtin_export(char **argv, t_env_list *env_list);
int		builtin_unset(char **argv, t_env_list *env_list);
int		builtin_env(char **argv, t_env_list *env_list);
int		builtin_exit(char **argv, t_env_list *env_list);
int		is_numeric(const char *str);

#endif