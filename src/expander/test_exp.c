/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:50:25 by tchernia          #+#    #+#             */
/*   Updated: 2025/05/08 19:14:07 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>

/* В парсингу ми маємо перевірити чи існує змінна від експорта (?) */

/* *raw - не оброблені, сирі дані */
#include <stdbool.h> 
#include <stdlib.h>
#include <stdio.h>

char	*extract_var(char *raw, long *len);
bool	is_valid_var(char *var);

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*dst;
	size_t			i;

	dst = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		dst[i] = c;
		i++;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb != 0 && __SIZE_MAX__ / nmemb < size)
		return (NULL);
	p = malloc(nmemb * size);
	if (!p)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	chr;

	chr = (unsigned char)c;
	while (*s != chr)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return ((char *)s);
}

char *ft_strndup(const char *s, long n)
{
    char    *new_str;
    int  i;

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

int is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*new_dest;
	const unsigned char	*new_src;

	if (n == 0 || dest == src)
		return (dest);
	new_dest = (unsigned char *)dest;
	new_src = (const unsigned char *)src;
	while (n--)
	{
		*new_dest++ = *new_src++;
	}
	return (dest);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (*src && size > 1)
	{
		*dst++ = *src++;
		size--;
	}
	*dst = '\0';
	return (src_len);
}


#include <unistd.h>
//we know we need to expand value
//starts only if we have symbol $ somewhere in line
char	*expand_value(char *raw)//, t_shell_type *shell)
{
	char	*result;
	char	*var;
	long		len; //size_t ?
	int		i;
	int		j;

	result = ft_calloc(ft_strlen(raw) + 1, sizeof(char));//як хендлити збільшення розміру при розгортанні?
	if (!result)
		return (NULL);//what we need to free ?
	i = 0;
	j = 0;
	len = 0;
	while (raw[i])
	{
		if (raw[i] == '$')
		{
			i++;
			// printf("i: %i\n", i);
			// char c = *(raw + i);
			// write(1, &raw[i], 1);
			// write(1, "\n", 1);
			// printf("raw + i: %c\n", *(raw + i));
			var = extract_var(raw + i, &len);
			//printf("len variable: %ld \n", len);
			//printf("%s\n", var);
/* 			write(1, "this is var: ", 14);
			write(1, var, ft_strlen(var));
			write(1, "\n", 1); */
			ft_memcpy(result + j, var, len + 1);
			i+=len;
			j+=len;
		}
		else
			result[j] = raw[i];
		i++;
		j++;
	}
	return (result);
}

//somethinf after $ {} or just var_name
char	*extract_var(char *raw, long *len)
{
	if (*raw == '{' && ft_strchr(raw, '}') != 0)
	{
		// printf("\nwe are in {}\n");
		*len = ft_strchr(raw, '}') - raw + 1;//щоб урахувати {} бо треба змістити ітератор на всю довжину key_var
		// printf("Found {...}, len: %ld\n", *len);
		return(ft_strndup(raw + 1, *len - 2));
	}
	else
	{
		// printf("\nwithout\n");
		while (raw[*len] && !is_whitespace(raw[*len]))
			(*len)++;
		return(ft_strndup(raw, *len + 1));
	}
	return (NULL);//we need it in case after $ we have '\0'
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool	is_valid_var(char *var)
{
	if (ft_isalpha(*var) || *var == '_')
		return (true);
	return (false);
}


int	main()
{
	printf("%s\n", expand_value("hello $USER word! ${tyty}"));
	printf("%s\n", expand_value("Hello $kli word $ttt"));

	// printf("\n\nnext test\n\n");
	// expand_value("Hello ${PATH} word $ooo");
	// expand_value("Hello $kli word $ttt");

	return (0);
}

