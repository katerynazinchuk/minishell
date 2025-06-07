/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:28:19 by tchernia          #+#    #+#             */
/*   Updated: 2025/06/03 15:52:46 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

#include "minishell.h"

bool check_unmached_quotes(char *line);
bool last_pipe_error(char *line);
bool first_pipe_error(char *line);
char *join_input(char *line);
char *check_input(char *line);

#endif