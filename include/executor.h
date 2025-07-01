/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:37:53 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/01 14:14:37 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <fcntl.h>
# include <linux/limits.h>

typedef int	(*t_redir_handler)(t_redir *redir_list);
typedef int	(*t_builtin_fn)(char **argv, t_env_list *env_list);

typedef struct s_builtin
{
	char			*name;
	t_builtin_fn	func;
}	t_builtin;

/* -------------------------------------------------------------------------- */

void			executor(t_session	*session);
int				run_ast(t_ast_node *ast, t_session *session);
int				run_pipe(t_ast_node *ast, t_session *session);
pid_t			child_left(t_ast_node *node, t_session *session, int *pipe_fd);
pid_t			child_right(t_ast_node *node, t_session *session, int *pipe_fd);
int				run_cmd(t_ast_node *node, t_session *session);
int				apply_redir(t_redir *redir_list);
int				run_external(t_ast_node *node, t_session *session);
t_builtin_fn	get_builtin_fn(char *cmd);

/* -------------------------------------------------------------------------- */

char			**env_to_arr(t_env_list *env_list);
int				find_path(char **value, t_env_list *env_list);
void			free_arr(char **arr);
void			close_pipe_fd(int *pipe_fd);
void			restore_fd(t_session *session);
int				free_in_fork(t_session *session, char **env_arr);
bool			is_new_line(char *str);

/* -------------------------------------------------------------------------- */

int				create_env_node(t_env_type **input, const char *key,\
										const char *value);
int				update_env_node(const char *var, t_env_list *env_list,\
												char *new_data);
int				set_env(t_env_list *env_list, const char *var,\
												const char *value);
void			unset_env(t_env_list *env_list, const char *var);
int				builtin_echo(char **argv, t_env_list *env_list);
int				builtin_cd(char **argv, t_env_list *env_list);
int				builtin_pwd(char **argv, t_env_list *env_list);
int				builtin_export(char **argv, t_env_list *env_list);
int				builtin_unset(char **argv, t_env_list *env_list);
int				builtin_env(char **argv, t_env_list *env_list);
int				builtin_exit(char **argv, t_env_list *env_list);

#endif