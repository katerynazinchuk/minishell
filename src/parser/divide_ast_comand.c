/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_ast_comand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:34:04 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/01 11:41:52 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command_parsing	*allocate_structure(void);
static int					is_redirect_token(t_token *token);
static int					handle_redirect_token(t_token **current,\
										t_command_parsing *structure);
static int					handle_arg_token(t_token *current,\
										t_command_parsing *structure);

t_command_parsing	*extract_red_and_args(t_token *head, t_token *end)
{
	t_command_parsing	*structure;
	t_token				*current;

	if (!head || !end)
		return (NULL);
	structure = allocate_structure();
	if (!structure)
		return (NULL);
	current = head;
	while (current != end)
	{
		if (is_redirect_token(current))
		{
			if (handle_redirect_token(&current, structure))
				return (NULL);
		}
		else
		{
			if (handle_arg_token(current, structure))
				return (NULL);
		}
		current = current->next;
	}
	return (structure);
}

static int	handle_redirect_token(t_token **current,\
									t_command_parsing *structure)
{
	if (append_redirect(*current, structure))
	{
		free_structure(structure);
		return (1);
	}
	*current = (*current)->next;
	return (0);
}

static int	handle_arg_token(t_token *current, t_command_parsing *structure)
{
	if (append_args(current, structure))
	{
		free_structure(structure);
		return (1);
	}
	return (0);
}

static int	is_redirect_token(t_token *token)
{
	return (token->type == T_APPEND || token->type == T_HEREDOC
		|| token->type == T_IN || token->type == T_OUT);
}

static t_command_parsing	*allocate_structure(void)
{
	t_command_parsing	*structure;

	structure = malloc(sizeof(t_command_parsing));
	if (!structure)
	{
		check_error(ENOMEM, "Command parsing ", GENERAL);
		return (NULL);
	}
	structure->redirect = NULL;
	structure->args = NULL;
	return (structure);
}
