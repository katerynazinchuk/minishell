/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:49:11 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/05/02 13:52:05 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char *ft_strndup(const char *s, size_t n)
{
    char    *new_str;
    size_t  i;

    new_str = (char *)malloc(sizeof(char) * (n + 1));
    if (!new_str)
        return (NULL);
    i = 0;
    while (i < n && s[i])
    {
        new_str[i] = s[i];
        i++;
    }
    new_str[i] = '\0';
    return (new_str);
}

void print_tokens(t_token_list *list)
{
	t_token	*current;

	current = list->head;
	while (current)
	{
		printf("Token: [type = %d] [value = %s] [quotes = %u]\n", current->type, current->value, current->t_quote_type);
		current = current->next;
	}
}

int quotes_error(t_str_pos *lexer)
{
	printf("Error: No matching quotes found for token starting at index %d\n", lexer->start);
	return (0);
}