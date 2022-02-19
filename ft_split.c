/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 18:58:58 by jblythe           #+#    #+#             */
/*   Updated: 2021/04/09 16:39:57 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"

char	**where_is_my_mind(char **result, size_t n)
{
	if (--n)
		free(result[n]);
	free(result);
	return (NULL);
}

void	kekkek(char *s, int *i, char c)
{
	if (s[*i] != c)
		(*i)++;
}

char	**get_words(char **result, char *s, char c)
{
	int	i;
	int	l;
	int	f;

	i = 0;
	l = 0;
	f = 0;
	while (s[i])
	{
		kekkek(s, &i, c);
		if (s[i] == c || s[i] == '\0')
		{
			if (i - l > 0)
			{
				result[f++] = ft_substr(&s[l], 0, i - l);
				if (!(result[f - 1]))
					return (where_is_my_mind(result, f));
			}
			while (s[i] == c && s[i])
				i++;
			l = i;
		}
	}
	result[f] = NULL;
	return (result);
}

size_t	words_counter(char const *s, char c)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c)
			i++;
		if (s[i] == c || s[i] == '\0')
		{
			l++;
			while (s[i] == c && s[i])
				i++;
		}
	}
	return (l + 1);
}

char	**ft_split(char *s, char c)
{
	size_t	size;
	char	**result;

	if (!s)
	{
		return (NULL);
	}
	size = words_counter(s, c);
	result = (char **)malloc(sizeof(char *) * (size));
	if (!result)
		return (NULL);
	result = get_words(result, (char *)s, c);
	return (result);
}
