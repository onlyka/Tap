/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:45:50 by jblythe           #+#    #+#             */
/*   Updated: 2021/04/12 18:13:14 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_detected(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

int	search_sprites(const char *s, int c)
{
	int		i;

	i = 0;
	while (*s)
	{
		s++;
		if (*s == c)
			i++;
	}
	return (i);
}

int	find_one(t_all *all, int x, int y, char *vector)
{
	while (check_in_array(all, x, y) != 0)
	{
		if (all->map[y][x] == '1')
			return (1);
		else if (all->map[y][x] == '0' || all->map[y][x] == '2' ||
		all->map[y][x] == 'S' || all->map[y][x] == 'W' || all->map[y][x] ==
		'E' || all->map[y][x] == 'N')
		{
			if (vector[0] == '2')
				x -= vector[1] - '1';
			else
				x += vector[0] - '0';
			if (vector[1] == '2')
				y -= vector[1] - '1';
			else
				y += vector[1] - '0';
		}
		else
			return (0);
	}
	return (0);
}

int	map_checker(t_all *all)
{
	int	x;
	int	y;

	x = 0;
	y = -1;
	while (++y < all->line_count)
	{
		while (check_in_array(all, x, y) != '\0')
		{
			if (all->map[y][x] == '0' || all->map[y][x] == 'N' ||
				all->map[y][x] == 'S' || all->map[y][x] == 'W' ||
				all->map[y][x] == 'E' || all->map[y][x] == '2')
			{
				if (find_one(all, x, y, "10") != 1 || find_one(all,
						x, y, "20") != 1 || find_one(all, x, y, "02") != 1
					|| find_one(all, x++, y, "01") != 1)
					return (0);
			}
			else if (all->map[y][x] == '2' || all->map[y][x] == ' ' ||
			all->map[y][x] == '1')
				x++;
		}
		x = 0;
	}
	return (1);
}

int	map_parsing(t_all *all, char *path, int j)
{
	int		fd;
	char	*line;
	int		i;
	int		line_count;

	map_calc(all, &line_count, j, path);
	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error(all, "Not found map");
	while (i < line_count)
	{
		if (get_next_line(fd, &line) >= 0)
		{
			if (i >= j)
				(all->map)[i - j] = ft_strdup(line);
		}
		else
			print_error(all, "Not file");
		free(line);
		i++;
	}
	return (line_count - j);
}
