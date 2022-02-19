/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:24:12 by jblythe           #+#    #+#             */
/*   Updated: 2021/10/24 06:47:43 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(t_all *all)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y <= all->res_y / 2)
	{
		while (x < all->res_x)
		{

			my_mlx_pixel_put(all, x, y, all->c_color);
			x++;
		}
		x = 0;
		y++;
	}
	while (y > all->res_y / 2 && y < all->res_y)
	{
		while (x < all->res_x)
		{
			my_mlx_pixel_put(all, x, y, all->f_color);
			x++;
		}
		x = 0;
		y++;
	}
}

void draw_borders(t_all *all)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y <= all->res_y)
	{
		while (x < all->res_x)
		{
			if (x <= all->border_size || x > SCREEN_X - all->border_size || y <
				all->border_size || y > SCREEN_Y - all->border_size)
				my_mlx_pixel_put(all, x, y, 0x4e4f60);
			x++;
		}
		x = 0;
		y++;
	}
}
