/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:49:57 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/19 13:18:08 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(char **args)
{
	int i;

	if (args == NULL || *args == NULL)
		return ;

	i = 0;
	while (args[i])
	{
		printf("[%s] ", args[i]);
		i++;
	}
}

void	print_redirect(t_redir *head)
{
	char *map[4];

	map[0] = "<";
	map[1] = ">";
	map[2] = ">>";
	map[3] = "<<";

	while (head != NULL)
	{
		printf("%s'%s' ", map[head->type], head->connection);
		head = head->next;
	}
}

void	print_node(t_ast_node *node, int depth)
{
	char *map[2];

	t_ast_node *left;
	t_ast_node *right;
	int 		i;

	map[0] = "AST_PIPE:    ";
	map[1] = "AST_COMMAND: ";

	if (!node)
		return ;

	left = node->left;
	right = node->right;

	i = 0;
	while(i < depth)
	{
		printf(" ");
		i++;
	}
	printf("%s", map[node->type]);
	print_args(node->value);
	print_redirect(node->redir);
	printf("\n");
	print_node(left, depth + 1);
	print_node(right, depth + 1);
}

// void	print_ast(t_ast_node *ast, int level)
// {
//     int i;

//     if (!ast)
// 	{
//         return ;
// 	}
// 	i = -1;
// 	while(++i < level)
//         printf("  ");
//     if (ast->type == AST_PIPE)
//         printf("[PIPE]\n");
//     else if (ast->type == AST_COMMAND)
//     {
//         printf("[CMD]: ");
//         i = 0;
//         while (ast->value && ast->value[i])
//         {
//             printf("%s ", ast->value[i]);
//             i++;
//         }
//         printf("\n");
//     }
//     // Recursively print left and right children
//     print_ast(ast->left, level + 1);
//     print_ast(ast->right, level + 1);
// }

// void	print_redir_node(t_redir *redirect)
// {
// 	while(redirect)
// 	{
// 		printf("[type: %u] [connection: %s]\n", redirect->type, redirect->connection);
// 		redirect= redirect->next;
// 	}

// }
// void	print_redir_tree(t_ast_node *node)
// {
// 	if(!node)
// 		return ; 
// 	if(node->type == AST_COMMAND)
// 		print_redir_node(node->redir);
// 	print_redir_tree(node->left);
// 	print_redir_tree(node->right);
// }
// void	print_argv(char **argv)
// {
// 	int i = 0;
// 	while(argv[i])
// 	{
// 		printf("%s", argv[i]);
// 		i++;
// 	}
// }

// void	print_argv_tree(t_ast_node *node)
// {
// 	if(!node)
// 		return ; 
// 	if(node->value)
// 		print_argv(node->value);
// 	print_argv_tree(node->left);
// 	print_argv_tree(node->right);
// }

// void print_tokens(t_session *session)
// {
// 	t_token	*current;

// 	current = session->tokens->head;
// 	while (current)
// 	{
// 		printf("Token: [type = %d] [expanded = %s]\n", current->type, current->expanded);
// 		current = current->next;
// 	}
// }

// void print_tokens(t_token_list *list, t_env_list *env_list)
// {
// 	t_token	*current;

// 	current = list->head;
// 	expand_tokens(list, env_list);
// 	while (current)
// 	{
// 		printf("Token: [type = %d] [value = %s] [expanded = %s][quotes = %u]\n", current->type, current->value, current->expanded, current->q_type);
// 		current = current->next;
// 	}
// }