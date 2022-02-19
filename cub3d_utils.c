/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:32:06 by jblythe           #+#    #+#             */
/*   Updated: 2021/04/12 18:05:46 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

void	my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char	*dst;

	if (color != 0x0000FF)
	{
		if ((x >= 0 && x < all->res_x - 1) && (y >= 0 && y < all->res_y - 1))
		{
			dst = all->img->addr + (y * all->img->line_length + x
					* (all->img->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
	}
}

char	*ft_strdup(char *s1)
{
	char	*str;
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	check_in_array(t_all *all, int x, int y)
{
	if (y < all->line_count && y >= 0)
	{
		if (x >= 0 && x < ft_strlen(all->map[y]))
			return (all->map[y][x]);
	}
	return (0);
}

void	dir_normalize(float *dir)
{
	if (*dir >= PI_2)
		*dir -= PI_2;
	if (*dir <= 0)
		*dir += PI_2;
}

void	draw_vertical_line(t_all *all, int x, int posx, int id)
{
	int	y;
	int	lineh;
	int	y_tex;
	int	lineh_tex;

	lineh = CUBE_SIZE * all->res_y / all->hits[x].distance;
	lineh_tex = lineh;
	if (lineh > all->res_y)
		lineh = all->res_y;
	y = all->res_y / 2 + lineh / 2;
	y_tex = all->res_y / 2 + lineh_tex / 2;
	while (y > all->res_y / 2 - lineh / 2)
	{
		if (all->flipx < 0)
			my_mlx_pixel_put(all, x, y, all->texture[id][(int)((y_tex
						- all->res_y / 2 + lineh / 2) * 1.0 * 63
					/ lineh_tex + 1) *64
				+ ((posx + 1) * all->flipx)]);
		else
			my_mlx_pixel_put(all, x, y, all->texture[id][(int)((y_tex
						- all->res_y / 2 + lineh / 2) * 1.0 * 63 / lineh_tex)
				*64 + (posx * all->flipx)]);
		y--;
		y_tex--;
	}
}
