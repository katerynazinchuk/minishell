/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:05:29 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/15 16:09:03 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_command *parse_tokens 
// {
// 	collect all words from token lists, go throught tokens node list
//	if token->type == TOKEN_WORD, add to **argv array
// if (if token->type == TOKEN_PIPE)
// 		return new node AST_PIPE with left and right branches;
// 	else
// 		return new node AST_COMMAND or ????NODE_REDIRECT;
// }
t_ast_node *create_ast_node(t_ast_type type, char **command)
{
	t_ast_node *ast_node;

	ast_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	ast_node->type = type;
	ast_node->value = command;
	ast_node->redir = NULL;
	ast_node->left = NULL;
	ast_node->right = NULL;
	return (ast_node);
}

t_ast_node *build_tree(t_token *head, t_token *end)
{
	t_token *current;
	t_token *last_pipe;
	t_ast_node *node;
	t_redir *redirect;
	char **argv;

	current = head;
	last_pipe = NULL;
	while(current && current != end)
	{
		if(current->type == TOKEN_PIPE)
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
		extract_redirect(&current, end, node);
		argv = tokens_to_argv(head);
		node->value = argv;
		return (node);
	}

}

char	**tokens_to_argv(t_token *head)
{
	int count;
	t_token *main;

	main = head;
	count = 0;
	while(main && main->value != NULL && main->type == TOKEN_WORD)
	{
		count++;
		main = main->next;
	}
	char **argv = malloc(sizeof(char *) * (count + 1));
	if(!argv)
		return(NULL);
	main = head;
	count = 0;
	while(main && main->value != NULL && main->type == TOKEN_WORD)
	{
		argv[count] = ft_strdup(main->value);
		count++;
		main = main->next;
	}
	argv[count] = NULL;
	return (argv);
}

void free_ast(t_ast_node *ast)
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

void print_ast(t_ast_node *ast, int level)
{
    int i;

    if (!ast)
	{
        return ;
	}
	i = -1;
	while(++i < level)
        printf("  ");
    if (ast->type == AST_PIPE)
        printf("[PIPE]\n");
    else if (ast->type == AST_COMMAND)
    {
        printf("[CMD]: ");
        i = 0;
        while (ast->value && ast->value[i])
        {
            printf("%s ", ast->value[i]);
            i++;
        }
        printf("\n");
    }
    // Recursively print left and right children
    print_ast(ast->left, level + 1);
    print_ast(ast->right, level + 1);
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


