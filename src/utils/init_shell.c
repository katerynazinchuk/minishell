/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:27:31 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/15 18:49:41 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	shell->env_list = fill_env_list(env);
	shell->tokens = NULL;
	// *ast;
	shell->line = NULL;
	shell->last_exit_status = 0;
	shell->prompt = "minishell> ";
}
