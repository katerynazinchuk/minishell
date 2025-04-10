/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:02:48 by tchernia          #+#    #+#             */
/*   Updated: 2024/11/08 13:53:22 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# define FT_PRINTF_H

int		ft_printf(const char *f, ...);
ssize_t	ft_print_c(char c);
ssize_t	ft_print_str(char *str);
ssize_t	ft_print_id(int num);
ssize_t	ft_print_u(unsigned int num);
ssize_t	ft_print_x(unsigned long hex, const char c);
ssize_t	ft_print_p(uintptr_t p);

#endif
