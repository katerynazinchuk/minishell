/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:27:31 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/24 17:12:57 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	shell->env_list = fill_env_list(env);//TODO how we handle case if !shell->env_list ?
	shell->tokens = NULL;
	shell->ast = NULL;
	shell->line = NULL;
	shell->last_exit_status = 0;
	shell->prompt = "minishell> ";
}

void	cleanup_cycle(t_shell	*shell)
{
	if (shell->tokens)
	{
		free_token_list(shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->ast)
	{
		free_ast(shell->ast);
		shell->ast = NULL;
	}
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
}
// TODO if uncomment previous if statement we have code dump.
//Why? -> cause pointer after previuos free didnt set up for NULL

