/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:31:28 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/26 19:38:56 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "token.h"

typedef enum s_ast_type
{
	AST_PIPE,
	AST_COMMAND,
}	t_ast_type;

typedef enum e_red_type
{
	RED_IN,
	RED_OUT,
	RED_APPEND,
	RED_HEREDOC,
}	t_red_type;

/* -------------------------------------------------------------------------- */

typedef struct s_redir
{
	t_red_type		type;
	char			*connection;
	t_quoted		quoted;
	struct s_redir	*next;
}	t_redir;

typedef struct s_com_tokens
{
	t_token				*word;
	struct s_com_tokens	*next;
}	t_com_tokens;

typedef struct s_command_parsing
{
	t_redir			*redirect;
	t_com_tokens	*args;
}	t_command_parsing;

typedef struct s_ast_node
{
	t_ast_type			type;
	char				**value;
	t_redir				*redir;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

/* -------------------------------------------------------------------------- */

t_ast_node			*create_ast_node(t_ast_type type, char **command);
t_ast_node			*parse_pipe(t_token *head, t_token *end);
char				**tokens_to_argv(t_com_tokens *head);
void				free_ast(t_ast_node **ast);
t_red_type			define_redirection(t_tok_type token_type);
t_redir				*create_redirect_node(t_red_type red, char *connection, \
											t_quoted quoted);
t_command_parsing	*extract_red_and_args(t_token *head, t_token *end);
t_com_tokens		*extract_args(t_token *current);
t_redir				*extract_redirect(t_token *current);
int					append_redirect(t_token *current, \
										t_command_parsing *structure);
int					append_args(t_token *current, t_command_parsing *structure);
void				free_structure(t_command_parsing *structure);
void				free_redirects(t_redir *redir);

/* -------------------------------------------------------------------------- */

void				print_args(char **args);
void				print_redirect(t_redir *head);
void				print_node(t_ast_node *node, int depth);

#endif