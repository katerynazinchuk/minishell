/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:05:29 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/21 15:02:37 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_ast_node(t_ast_type type, char **command)
{
	t_ast_node	*ast_node;

	ast_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	ast_node->type = type;
	ast_node->value = command;
	ast_node->redir = NULL;
	ast_node->left = NULL;
	ast_node->right = NULL;
	return (ast_node);
}

t_ast_node	*build_tree(t_token *head, t_token *end)
{
	t_token *current;
	t_token *last_pipe;
	t_ast_node *node;
	t_command_parsing *structure;
	char **argv;

	current = head;
	last_pipe = NULL;
	while(current && current != end)
	{
		if(current->type == T_PIPE)
		last_pipe = current;
		current = current->next;
	}
	if(last_pipe)
	{
		node = create_ast_node(AST_PIPE, NULL);
		node->left = build_tree(head, last_pipe);
		node->right = build_tree(last_pipe->next, end);
		return (node);
	}
	else
	{
		
		current = head;
		node = create_ast_node(AST_COMMAND, NULL);
		structure = extract_red_and_ref(head, last_pipe);
		argv = tokens_to_argv(structure->referens);
		node->value = argv;
		node->redir = structure->redirect;
		return (node);
	}
}


char	**tokens_to_argv(t_com_tokens *head)
{
	int count;
	t_com_tokens *main;
	char **argv;

	main = head;
	count = 0;
	while(main && main->word != NULL && main->word->type == T_WORD)
	{
		count++;
		main = main->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if(!argv)
		return(NULL);
	main = head;
	count = 0;
	while(main && main->word != NULL && main->word->type == T_WORD)
	{
		argv[count] = ft_strdup(main->word->expanded);
		if(!argv[count])
		{
			while(--count >= 0)
				free(argv[count]);
			free(argv);
			return (NULL);
		}
		count++;
		main = main->next;
	}
	argv[count] = NULL;
	return (argv);
}

void	free_ast(t_ast_node *ast)
{
	int	i;

	if(!ast)
		return;
	free_ast(ast->left);
	free_ast(ast->right);
	i = 0;
	if(ast->value)
	{
		while(ast->value[i])
		{
			free(ast->value[i]);
			i++;
		}
		free(ast->value);
	}
	free(ast);
}

// Print errors:
// if string starts with |
// if > >> << without argument
// if unrecognized tokens
// return NULL or error struct if input is invalid


// add debug function:
// print_command_list(t_command *)

// function to free memory for **argv
// function to free memory for t_command

//char* last_pipe = strrchr(input, '|');


