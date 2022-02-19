/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 14:23:08 by jblythe           #+#    #+#             */
/*   Updated: 2021/04/07 22:11:40 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	k;

	k = 0;
	i = 0;
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	if (s == NULL)
		return (NULL);
	while ((s[i] && k < len))
	{
		if (start <= i)
		{
			str[k] = s[i];
			k++;
		}
		i++;
	}
	str[k] = '\0';
	return (str);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_chr_pos(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s != c)
	{
		if (*s == '\0')
			return (-1);
		s++;
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (*s != c)
	{
		if (*s == '\0')
			return (0);
		s++;
		i++;
	}
	return ((char *)s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		a;
	int		b;
	int		i;

	i = 0;
	a = 0;
	b = 0;
	if (s1 && s2)
	{
		if (s1)
			a = ft_strlen(s1);
		if (s2)
			b = ft_strlen(s2);
		str = malloc((a + b + 1) * sizeof(char));
		if (!str)
			return (NULL);
		while (*s1)
			str[i++] = *s1++;
		while (*s2)
			str[i++] = *s2++;
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
