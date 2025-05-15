/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:19:42 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/15 18:05:23 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_red_type define_redirection(t_tok_type token_type)
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

t_redir *create_redirect_node(t_red_type red, char *connection)
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

void add_to_redirect(t_ast_node *node, t_redir *new)
{
	t_redir *current;

	if (!new || !node)
		return;
	if (!node->redir)
		node->redir = new;
	else
	{
		current = node->redir;
		while(current->next)
			current = current->next;
		current->next = new;
	}
}

void exract_redirection_list(t_token **head, t_token *end, t_ast_node *node)
{
	t_token *prev;
	t_token *current;
	t_token *next;//for target
	t_token *new_head;
	t_token *last_word;
	t_redir *redirect;
	t_red_type type;

	prev = NULL;
	current = head;
	next = NULL;
	new_head = NULL;
	last_word = NULL;
	while(current && current != end)
	{
		if(current->type == T_IN || current->type == T_OUT || current->type == T_APPEND || current->type == T_HEREDOC) 
		{
			next = current->next;
			if(!next || next->type != T_WORD)
			{
				return ;
			}
			type = define_redirection(current->type);
			redirect = create_redirect_node(type, next->value);
			add_to_redirect(node, redirect);
			current = next->next;
			continue;
		}
		if(current->value)
		current = current->next;
	}
}

