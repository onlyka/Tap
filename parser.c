/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:51:49 by jblythe           #+#    #+#             */
/*   Updated: 2021/10/22 21:03:48 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hide_line_check(char **line, int *j, char ***split)
{
	if ((*split)[0] == '\0')
	{
		free(*line);
		free_all_arg(split);
		(*j)++;
		return (1);
	}
	return (0);
}

void	res_check(t_all *all, char ***split, char **line)
{
	all->res_x = ft_atoi((*split)[1]);
	all->res_y = ft_atoi((*split)[2]);
	if (all->res_x > SCREEN_X)
		all->res_x = SCREEN_X;
	if (all->res_y > SCREEN_Y)
		all->res_y = SCREEN_Y;
	if (all->res_x < 200 && all->res_x > 0)
		all->res_x = 200;
	if (all->res_y < 200 && all->res_y > 0)
		all->res_y = 200;
	if (all->res_x == -1 || all->res_y == -1 || arg_overflow((*split)[1],
		9) == 0 || arg_overflow((*split)[2], 9) == 0
	|| all->res_x <= 0 || all->res_y <= 0)
	{
		free(*line);
		free_all_arg(split);
		print_error(all, "Not correct resolution");
	}
}

void	parser(t_all *all, char *path)
{
	int		fd;
	char	*line;
	int		j;
	char	**split;

	j = 0;
	fd = open_cub(all, path);
	while (get_next_line(fd, &line) >= 0)
	{
		split = ft_split(line, ' ');
			all->line_count = map_parsing(all, path, j);
			kek3(&line, &split);
			break ;
//		}
		kek3(&line, &split);
		j++;
	}
}
