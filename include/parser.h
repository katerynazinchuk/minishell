/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:31:28 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/17 12:28:08 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

typedef enum s_ast_type
{
	AST_PIPE,
	AST_COMMAND,
	//AST REDIRECT
}	t_ast_type;

typedef enum e_red_type
{
	RED_IN,//<
	RED_OUT,//>
	RED_APPEND,//>>
	RED_HEREDOC,//<<
}	 t_red_type;

typedef struct s_redir
{
	t_red_type type;
	char *connection;//filename or heredoc delimetr
	struct s_red *next;
}	t_redir;

typedef struct s_com_tokens//for dereferenses words for argv
{
	char				*word;
	struct s_com_tokens	*next;
}	t_com_tokens;

typedef struct s_ast_node
{
	t_ast_type			type; 
	char				**value;//command
	t_redir				*redir;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

//one node for the ast???
typedef struct s_command {
    char				**argv;            // command + arguments
    char				*infile;           // for `<`
    char				*outfile;          // for `>` or `>>`
    int					append_mode;        // 1 if >>, 0 if >
    int					is_heredoc;         // 1 if heredoc, 0 otherwise
    char				*heredoc_delim;    // heredoc delimiter
    struct s_command	*next; // next in pipe chain
}	t_command;

typedef struct s_command_parsing
{
	t_redir *redirect;
	t_com_tokens *referens;
} t_command_parsing;



t_ast_node	*create_ast_node(t_ast_type type, char **command);
t_ast_node	*build_tree(t_token *head, t_token *end);
char		**tokens_to_argv (t_token *head);
void		free_ast(t_ast_node *ast);
void		print_ast(t_ast_node *ast, int level);

t_red_type define_redirection(t_tok_type token_type);
t_redir *create_redirect_node(t_red_type red, char *connection);
void add_to_redirect(t_ast_node *node, t_redir *new);
t_com_tokens *extract_referens(t_token *current);
t_redir *extract_redirect(t_token *current);
int	append_red(t_token *current, t_command_parsing *structure);
int	append_ref(t_token *current, t_command_parsing *structure);
t_command_parsing *extract_red_and_ref(t_token *head);

#endif

//The last unquoted pipe is usually the root node
// | is higher than > in shell grammar (because it's at the top level)