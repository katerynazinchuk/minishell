/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:05:29 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/30 14:25:35 by kzinchuk         ###   ########.fr       */
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
	char **argv;

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
		printf("minishell: syntax error near unexpected token `%s`\n", head->expanded);
		free_ast(new_ast_node);
		return (NULL);
	}
	argv = tokens_to_argv(structure->args);
	new_ast_node->value = argv;
	new_ast_node->redir = structure->redirect;
	return (new_ast_node);
}

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
		{
			printf("minishell: memory allocation error\n");
			return (NULL);
		}
		new_ast_node->left = parse_pipe(head, last_pipe);
		if (!new_ast_node->left)
		{
			free_ast(new_ast_node);
			return (NULL);
		}
		new_ast_node->right = parse_command(last_pipe->next, end);
		if (!new_ast_node->right)
		{
			free_ast(new_ast_node);
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


