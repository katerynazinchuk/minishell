/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:03:54 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/22 15:44:52 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

char *ft_strndup(const char *s, size_t n);
int	is_whitespace(char c);
int	is_special_char(char c);
void	ignore_args(int argc, char **argv);
// int	print_str_fd(const char *str, )
#endif