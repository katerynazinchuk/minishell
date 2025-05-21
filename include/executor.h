/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:37:53 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/21 13:38:02 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef struct	s_command
{
    char				**argv;            // command + arguments
    char				*infile;           // for `<`
    char				*outfile;          // for `>` or `>>`
    int					append_mode;        // 1 if >>, 0 if >
    int					is_heredoc;         // 1 if heredoc, 0 otherwise
    char				*heredoc_delim;    // heredoc delimiter
    struct s_command	*next; // next in pipe chain
}	t_command;

//???