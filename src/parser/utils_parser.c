/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:31:01 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/07/01 16:19:33 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_argv_tokens(t_com_tokens *head);
static char	**allocate_argv_array(int count);
static int	move_to_argv(char **argv, int count, t_com_tokens *cur);
void		free_argv_array(char **argv, int count);

char	**tokens_to_argv(t_com_tokens *head)
{
	int				count;
	t_com_tokens	*cur;
	char			**argv;

	count = count_argv_tokens(head);
	argv = allocate_argv_array(count);
	if (!argv)
		return (NULL);
	cur = head;
	count = 0;
	while (cur && cur->word != NULL && cur->word->type == T_WORD)
	{
		if (cur->word->expanded)
		{
			if (move_to_argv(argv, count, cur))
				return (NULL);
			count++;
		}
		cur = cur->next;
	}
	argv[count] = NULL;
	return (argv);
}

static int	count_argv_tokens(t_com_tokens *head)
{
	int				count;
	t_com_tokens	*cur;

	cur = head;
	count = 0;
	while (cur && cur->word != NULL && cur->word->type == T_WORD)
	{
		if (cur->word->expanded)
			count++;
		cur = cur->next;
	}
	return (count);
}

static char	**allocate_argv_array(int count)
{
	char	**argv;

	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
	{
		check_error(ENOMEM, "command parsing: ", GENERAL);
		return (NULL);
	}
	return (argv);
}

static int	move_to_argv(char **argv, int count, t_com_tokens *cur)
{
	argv[count] = ft_strdup(cur->word->expanded);
	if (!argv[count])
	{
		free_argv_array(argv, count);
		check_error(ENOMEM, "minishell: command parsing: ", GENERAL);
		return (1);
	}
	return (0);
}

void	free_argv_array(char **argv, int count)
{
	while (--count >= 0)
		free(argv[count]);
	free(argv);
}
