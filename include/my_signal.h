/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:58:28 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/27 16:30:35 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SIGNAL_H
# define MY_SIGNAL_H

# include <signal.h>

typedef enum e_sigtype
{
	MAIN_SIG,
	HEREDOC_SIG,
	DEFAULT_SIG,
}	t_sigtype;

void	sigint_main(int signal_type);
void	sigint_heredoc(int signal_type);
void	setsignal(t_sigtype type);

#endif