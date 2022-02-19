/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 14:22:16 by jblythe           #+#    #+#             */
/*   Updated: 2021/04/10 20:34:54 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	remainder_and_line_rewrite(char *buf, char **line, char **remainder)
{
	char	*tmp;
	char	*tmp1;

	tmp1 = ft_substr(buf, 0, ft_chr_pos(buf, '\n'));
	tmp = *line;
	*line = ft_strjoin(*line, tmp1);
	free(tmp);
	free(tmp1);
	if (ft_strlen(buf) > ft_chr_pos(buf, '\n'))
	{
		tmp = *remainder;
		*remainder = ft_substr(buf, ft_chr_pos(buf, '\n') + 1, ft_strlen(buf)
				- (ft_chr_pos(buf, '\n')));
		free(tmp);
	}
	free(buf);
	return (1);
}

int	reading(int fd, char *buf, char **remainder, char **line)
{
	char	*tmp;
	int		i;

	i = read(fd, buf, BUFFER_SIZE);
	while (i > 0)
	{
		if (i < 0)
		{
			free(buf);
			free(*remainder);
			*remainder = NULL;
			return (-1);
		}
		buf[i] = '\0';
		if (ft_strchr(buf, '\n'))
			return (remainder_and_line_rewrite(buf, line, remainder));
		else
		{
			tmp = *line;
			*line = ft_strjoin(*line, buf);
			free(tmp);
		}
		i = read(fd, buf, BUFFER_SIZE);
	}
	return (0);
}

int	remainder_contol(char **remainder, char **line, char **buf)
{
	char	*tmp;

	if (*remainder)
	{
		tmp = *line;
		if (ft_chr_pos(*remainder, '\n') >= 0)
			*line = ft_substr(*remainder, 0, ft_chr_pos(*remainder, '\n'));
		else
			*line = ft_substr(*remainder, 0, ft_strlen(*remainder));
		free(tmp);
		if (ft_chr_pos(*remainder, '\n') >= 0)
		{
			if (ft_strlen(*remainder) > ft_chr_pos(*remainder, '\n'))
			{
				tmp = *remainder;
				*remainder = ft_substr(*remainder, ft_chr_pos(*remainder,
							'\n') + 1, ft_strlen(*remainder)
						- (ft_chr_pos(*remainder, '\n')));
				free(tmp);
			}
			free(*buf);
			return (1);
		}
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	int			i;
	static char	*remainder = NULL;

	buf = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || !line || BUFFER_SIZE < 1 || !buf)
	{
		free(remainder);
		remainder = NULL;
		return (-1);
	}
	*line = malloc(1);
	**line = '\0';
	if (remainder_contol(&remainder, line, &buf) == 1)
		return (1);
	i = reading(fd, buf, &remainder, line);
	if (i == -1)
		return (-1);
	else if (i == 1)
		return (1);
	free(remainder);
	remainder = NULL;
	free(buf);
	return (0);
}
