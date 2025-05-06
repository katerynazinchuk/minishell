/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:31:28 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/06 18:00:21 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

typedef enum s_ast_type
{
	AST_PIPE,
	AST_COMMAND,
}	t_ast_type;

//

typedef struct s_ast
{
	t_ast_type	ast_type; 
	t_ast		*left;
	t_ast		*rigt;
}	t_ast;

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


#endif

//The last unquoted pipe is usually the root node
// | is higher than > in shell grammar (because it's at the top level)