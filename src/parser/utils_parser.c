/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:31:01 by kzinchuk          #+#    #+#             */
/*   Updated: 2025/06/27 13:30:07 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokens_to_argv(t_com_tokens *head)
{
	int				count;
	t_com_tokens	*cur;
	char			**argv;

	cur = head;
	count = 0;
	while (cur && cur->word != NULL && cur->word->type == T_WORD)
	{
		if (cur->word->expanded && cur->word->expanded[0] != '\0')
			count++;
		cur = cur->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
	{
		check_error(ENOMEM, "command parsing: ", GENERAL);
		return (NULL);
	}
	cur = head;
	count = 0;
	while (cur && cur->word != NULL && cur->word->type == T_WORD)
	{
		if (cur->word->expanded && cur->word->expanded[0] != '\0')
		{
			argv[count] = ft_strdup(cur->word->expanded);
			if (!argv[count])
			{
				while (--count >= 0)
					free(argv[count]);
				free(argv);
				check_error(ENOMEM, "command parsing: ", GENERAL);
				return (NULL);
			}
			count++;
		}
		cur = cur->next;
	}
	argv[count] = NULL;
	return (argv);
}

