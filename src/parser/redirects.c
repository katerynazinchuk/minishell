/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:19:42 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/25 16:29:05 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red_type	define_redirection(t_tok_type token_type)
{
	if(token_type == T_IN)
		return(RED_IN);
	if(token_type == T_OUT)
		return(RED_OUT);
	if(token_type == T_APPEND)
		return(RED_APPEND);
	if(token_type == T_HEREDOC)
		return(RED_HEREDOC);
	return (-1);//??
}

t_redir	*create_redirect_node(t_red_type red, char *connection, t_quoted quoted)
{
	t_redir *redirect;
	
	redirect = (t_redir *)malloc(sizeof(t_redir));
	if(!redirect)
		return (NULL);
	redirect->type = red;
	redirect->connection = ft_strdup(connection);
	redirect->quoted = quoted;
	redirect->next = NULL;
	return (redirect);
}

t_com_tokens *extract_args(t_token *current)
{
	t_com_tokens *new_ref;

	new_ref = malloc(sizeof(t_com_tokens));
	if(!new_ref)
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
	t_token *next;
	t_redir *new_redir;
	
	next = current->next;
	if(!next || next->type != T_WORD)
	{
		check_error(SYNTAX_ERR, "near unexpected token `newline'", GENERAL);//TODO  text for error
		return (NULL);
	}
	new_redir = create_redirect_node(
		define_redirection(current->type), next->expanded,
		next->quoted);
	if(!new_redir)
	{
		check_error(ENOMEM, "create redirection", GENERAL);
		return (NULL);//only allocate error
	}
	return(new_redir);
}

int	append_redirect(t_token *current, t_command_parsing *structure)
{
	t_redir	*new_red;
	t_redir	*tmp;

	new_red = extract_redirect(current);
	if(!new_red)
		return (1);
	if(!structure->redirect)
		structure->redirect = new_red;
	else
	{
		tmp = structure->redirect;
		while(tmp->next)
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
	if(!new_ref)
		return (1);
	if(!structure->args)
		structure->args = new_ref;
	else
	{
		tmp = structure->args;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = new_ref;
	}
	return (0);
}

t_command_parsing *extract_red_and_args(t_token *head, t_token *end)
{
	t_command_parsing	*structure;
	t_token				*current;
	
	if(!head || !end)
		return (NULL);
	structure = malloc(sizeof(t_command_parsing));
	if(!structure)
	{
		check_error(ENOMEM, "Command parsing ", GENERAL);
		return (NULL);
	}
	structure->redirect = NULL;
	structure->args = NULL;
	
	current = head;
	while(current != end)
	{
		if(current->type == T_APPEND || current->type == T_HEREDOC ||
			current->type == T_IN || current->type == T_OUT )
		{
			if (append_redirect(current, structure))
			{
				free_structure(structure);
				return (NULL);
			}
			current = current->next;
		}
		else 
		{
			if(append_args(current, structure))
			{
				free_structure(structure);
				return (NULL);
			}
		}
		current = current->next;
	}
	return (structure);
}

