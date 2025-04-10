/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:49:18 by tchernia          #+#    #+#             */
/*   Updated: 2024/10/23 12:22:16 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_count_words(char const *s, char c);
static char		*ft_word(const char *start, size_t length);
static char		**ft_alloc_and_fill(char const *s, char c, size_t count_words);
static void		ft_free_mem(char **array);

char	**ft_split(char const *s, char c)
{
	size_t	count_words;
	char	**split_s;

	if (!s)
		return (NULL);
	count_words = ft_count_words(s, c);
	if (count_words == 0)
	{
		split_s = (char **)malloc(sizeof(char *));
		if (!split_s)
			return (NULL);
		split_s[0] = NULL;
		return (split_s);
	}
	return (ft_alloc_and_fill(s, c, count_words));
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count_words;
	int		in_word;

	count_words = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count_words++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count_words);
}

static char	*ft_word(const char *start, size_t length)
{
	char	*word;
	size_t	i;

	word = (char *)malloc((length + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < length)
	{
		word[i] = start[i];
		i++;
	}
	word[length] = '\0';
	return (word);
}

static void	ft_free_mem(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**ft_alloc_and_fill(char const *s, char c, size_t count_words)
{
	char	**word_array;
	size_t	i;
	size_t	word_len;

	word_array = (char **)malloc((count_words + 1) * sizeof(char *));
	if (!word_array)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_len = 0;
			while (s[word_len] && s[word_len] != c)
				word_len++;
			word_array[i] = ft_word(s, word_len);
			if (!word_array[i++])
				return (ft_free_mem(word_array), NULL);
			s += word_len;
		}
		else
			s++;
	}
	word_array[i] = NULL;
	return (word_array);
}
