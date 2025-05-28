/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:19:42 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/28 17:35:45 by kzinchuk         ###   ########.fr       */
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
	return (-1);
}

t_redir	*create_redirect_node(t_red_type red, char *connection)
{
	t_redir *redirect;
	
	redirect = (t_redir *)malloc(sizeof(t_redir));
	if(!redirect)
		return (NULL);
	redirect->type = red;
	redirect->connection = ft_strdup(connection);
	redirect->next = NULL;
	return (redirect);
}

// void	add_to_redirect(t_ast_node *node, t_redir *new)
// {
// 	t_redir *current;

// 	if (!new || !node)
// 		return;
// 	if (!node->redir)
// 		node->redir = new;
// 	else
// 	{
// 		current = node->redir;
// 		while(current->next)
// 			current = current->next;
// 		current->next = new;
// 	}
// }

t_com_tokens	*extract_referens(t_token *current)
{
	t_com_tokens *new_ref;

	new_ref = malloc(sizeof(t_com_tokens));
	if(!new_ref)
		return (NULL);
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
		return (NULL);
	new_redir = create_redirect_node(define_redirection(current->type), next->expanded);
	if(!new_redir)
		return (NULL);
	return(new_redir);
}
int	append_red(t_token *current, t_command_parsing *structure)
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
	
int	append_ref(t_token *current, t_command_parsing *structure)
{
	t_com_tokens	*new_ref;
	t_com_tokens	*tmp;

	new_ref = extract_referens(current);
	if(!new_ref)
		return (1);
	
	if(!structure->referens)
		structure->referens = new_ref;
	else
	{
		tmp = structure->referens;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = new_ref;
	}
	return (0);
}

t_command_parsing *extract_red_and_ref(t_token *head, t_token *end)
{
	t_command_parsing	*structure;
	t_token				*current;
	
	if(!head)
		return (NULL);
	structure = malloc(sizeof(t_command_parsing));
	if(!structure)
		return (NULL);
	structure->redirect = NULL;
	structure->referens = NULL;
	
	current = head;
	while(current && current != end)
	{
		if(current->type == T_APPEND || current->type == T_HEREDOC ||\
			current->type == T_IN || current->type == T_OUT)
		{
			if (append_red(current, structure))
			{
				//free_command_parsing(structure); //before & NULL
				return (NULL);
			}
			current = current->next;
			//return (free_structure(structure), NULL);//catch error end show msg allocate fail
		}
		else 
		{
			if(append_ref(current, structure))
			{
				//free_command_parsing(structure);
				return (NULL);
			}
		}
		current = current->next;
	}
	return (structure);
}

// void free_command_parsing(t_command_parsing *structure)
// {
	
// }