/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:48:28 by jblythe           #+#    #+#             */
/*   Updated: 2021/04/12 18:20:00 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

int	arg_overflow(char *line, int size)
{
	if (ft_strlen((const char *)line) >= 1 && ft_strlen((const char *)line)
		<= size)
		return (1);
	return (0);
}

int	get_arg_count(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int	ft_atoi(const char *c)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	if (*c == '-' || *c == '+')
	{
		if (*c++ == '-')
			sign *= -1;
	}
	while (*c)
	{
		if (*c >= '0' && *c <= '9')
		{
			res += (*c++ - '0');
			res *= 10;
		}
		else
			return (-1);
	}
	return (res / 10 * sign);
}

int	ft_strncmp(char *s1, char *s2, int n, int flag)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	if (ft_strlen((char *)s1) != ft_strlen((char *)s2) && flag == 0)
		return (-1);
	while (n--)
	{
		if ((*a != *b) || (!*a || !*b))
			return (*a - *b);
		a++;
		b++;
	}
	return (0);
}

void	map_calc(t_all *all, int *line_count, int j, char *path)
{
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error(all, "Not found map");
	*line_count = 0;
	all->sprites_count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		(*line_count)++;
		all->sprites_count += search_sprites(line, '2');
		free(line);
	}
	if (*line_count > 0)
	{
		free(line);
		all->map = malloc(sizeof(char *) * ++(*line_count) - j);
	}
}
