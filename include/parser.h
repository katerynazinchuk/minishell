/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:31:28 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/17 12:14:10 by kzinchuk         ###   ########.fr       */
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

//

typedef struct s_ast_node
{
	char				**value;//command
	//char	*filename?

	t_ast_type			type; 
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


t_ast_node	*create_ast_node(t_ast_type type, char **command);
t_ast_node	*build_tree(t_token *head, t_token *end);
char		**tokens_to_argv (t_token *head);
void		free_ast(t_ast_node *ast);
void		print_ast(t_ast_node *ast, int level);

#endif

//The last unquoted pipe is usually the root node
// | is higher than > in shell grammar (because it's at the top level)