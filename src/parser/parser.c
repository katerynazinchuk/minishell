/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:05:29 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/20 14:23:49 by tchernia         ###   ########.fr       */
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


t_ast_node *parse_command(t_token *head, t_token *end)
{
	t_token *current;
	t_ast_node *new_ast_node;
	t_command_parsing *structure;

	current = head;
	new_ast_node = create_ast_node(AST_COMMAND, NULL);
	if (!new_ast_node)
	{
		printf("minishell: memory allocation error\n");
		return (NULL);
	}
	structure = extract_red_and_args(head, end);
	if (!structure)
	{
		write(1, "no struct\n", 11);
		free_ast(&new_ast_node);
		return (NULL);
	}
	new_ast_node->value = tokens_to_argv(structure->args);
	if(!new_ast_node->value)
		return (NULL);//??
	new_ast_node->redir = structure->redirect;
	
	free_structure(structure);
	// free(structure);
	return (new_ast_node);
}

// typedef struct	s_command_parsing
// {
// 	t_redir			*redirect;
// 	t_com_tokens	*args;
// }	t_command_parsing;




t_ast_node *parse_pipe(t_token *head, t_token *end)
{
	t_token *current;
	t_token *last_pipe;
	t_ast_node *new_ast_node;
	
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
		new_ast_node = create_ast_node(AST_PIPE, NULL);
		if(!new_ast_node)
			return (NULL);// need to clean previous node recursevly???
		new_ast_node->left = parse_pipe(head, last_pipe);
		if (!new_ast_node->left)
		{
			free_ast(&new_ast_node);
			return (NULL);
		}
		new_ast_node->right = parse_command(last_pipe->next, end);
		if (!new_ast_node->right)
		{
			free_ast(&new_ast_node);
			return (NULL);
		}
		return (new_ast_node);
	}
	return (parse_command(head, end));
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



// Print errors:
// if string starts with |
// if string ends with | - than call readline and join results
// if > >> << without argument
// return NULL or error struct if input is invalid


// add debug function:
// print_command_list(t_command *)


