/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:19:42 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/02 17:42:00 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*create_redirect_node(t_red_type red, char *connection, t_quoted quoted)
{
	t_redir	*redirect;

	redirect = (t_redir *)malloc(sizeof(t_redir));
	if (!redirect)
		return (NULL);
	redirect->type = red;
	redirect->connection = ft_strdup(connection);
	if (!redirect->connection)
		return (NULL);
	redirect->quoted = quoted;
	redirect->next = NULL;
	return (redirect);
}

t_com_tokens	*extract_args(t_token *current)
{
	t_com_tokens	*new_ref;

	new_ref = malloc(sizeof(t_com_tokens));
	if (!new_ref)
	{
		check_error(ENOMEM, "create arguments", GENERAL);
		return (NULL);
	}
	new_ref->word = current;
	new_ref->next = NULL;
	return (new_ref);
}

t_redir	*extract_redirect(t_token *current)
{
	t_token	*next;
	t_redir	*new_redir;

	next = current->next;
	if (!next || next->type != T_WORD)
	{
		check_error(SYNTAX_ERR, "near unexpected token `newline'", GENERAL);
		return (NULL);
	}
	new_redir = create_redirect_node(define_redirection(current->type), \
next->expanded, next->quoted);
	if (!new_redir)
	{
		check_error(ENOMEM, "create redirection", GENERAL);
		return (NULL);
	}
	return (new_redir);
}

int	append_redirect(t_token *current, t_command_parsing *structure)
{
	t_redir	*new_red;
	t_redir	*tmp;

	new_red = extract_redirect(current);
	if (!new_red)
		return (1);
	if (!structure->redirect)
		structure->redirect = new_red;
	else
	{
		tmp = structure->redirect;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_red;
	}
	return (0);
}

int	append_args(t_token *current, t_command_parsing *structure)
{
	t_com_tokens	*new_ref;
	t_com_tokens	*tmp;

	new_ref = extract_args(current);
	if (!new_ref)
		return (1);
	if (!structure->args)
		structure->args = new_ref;
	else
	{
		tmp = structure->args;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_ref;
	}
	return (0);
}
