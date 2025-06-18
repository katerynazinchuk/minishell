/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Amirre <Amirre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:03:54 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/18 22:10:21 by Amirre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

char *ft_strndup(const char *s, size_t n);
int	is_whitespace(char c);
int	is_special_char(char c);
void	ignore_args(int argc, char **argv);

#endif