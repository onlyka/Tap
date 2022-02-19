/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:51:04 by jblythe           #+#    #+#             */
/*   Updated: 2021/10/23 17:08:06 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vectord	check_horizontal_lines(t_all *all, t_vectord hit, float dir)
{
	t_vectord	a;
	t_vectord	b;
	int			d;
	t_vectord	pos;

	pos.x = 2147483647;
	pos.y = 2147483647;
	dir_normalize(&dir);
	if (check_horizontal_error(dir, hit, &a, &d) == 1)
		return (pos);
	b.x = CUBE_SIZE / tan(dir) *d;
	b.y = CUBE_SIZE * d;
	while (check_in_array(all, (int)(a.x / CUBE_SIZE),
		(int)(a.y / CUBE_SIZE) - ((d == -1) ? 1 : 0)) != '1')
	{
		a.x = a.x + b.x;
		a.y = a.y + b.y;
		if (a.x / CUBE_SIZE * SCALE > all->res_x || a.x / CUBE_SIZE * SCALE < 0
			|| a.y / CUBE_SIZE * SCALE > all->res_y || a.y / CUBE_SIZE
			* SCALE < 0)
			return (pos);
	}
	pos.x = a.x;
	pos.y = a.y;
	return (pos);
}

t_vectord	check_vertical_lines(t_all *all, t_vectord hit, float dir)
{
	t_vectord	a;
	t_vectord	b;
	int			d;
	t_vectord	pos;

	pos.x = 2147483647;
	pos.y = 2147483647;
	dir_normalize(&dir);
	if (check_vert_error(dir, hit, &b, &d) == 1)
		return (pos);
	a.x = CUBE_SIZE * d * -1;
	a.y = CUBE_SIZE * tan(dir) *d * -1;
	while (check_in_array(all, (int)(b.x / CUBE_SIZE) - ((d == 1) ? 1 : 0),
		(int)(b.y / CUBE_SIZE)) != '1')
	{
		b.x = b.x + a.x;
		b.y = b.y + a.y;
		if (b.x / CUBE_SIZE * SCALE > all->res_x || b.x / CUBE_SIZE
			* SCALE < 0 || b.y / CUBE_SIZE * SCALE > all->res_y || b.y
			/ CUBE_SIZE * SCALE < 0)
			return (pos);
	}
	pos.x = b.x;
	pos.y = b.y;
	return (pos);
}

void	check_distance_posv(t_all *all, t_vectordf distance,
								t_vectord posv, int x)
{
	if (distance.x <= distance.y)
	{
		all->hits[x].distance = distance.x * cos(all->player->left
				- all->player->dir);
		if (all->hits->pos.x > posv.x)
			all->flipx = -1;
		else
			all->flipx = 1;
//		if (all->hits->pos.x > posv.x)
//			draw_vertical_line(all, x, (int)posv.y
//				% CUBE_SIZE, 0);
//		else
//			draw_vertical_line(all, x, (int)posv.y
//				% CUBE_SIZE, 1);
	}
}

void	check_distance_posh(t_all *all, t_vectordf distance,
								t_vectord posh, int x)
{
	if (distance.x > distance.y)
	{
		all->hits[x].distance = distance.y * cos(all->player->left
				- all->player->dir);
		if (all->hits->pos.y > posh.y)
			all->flipx = 1;
		else
			all->flipx = -1;
//		if (all->hits->pos.y > posh.y)
//			draw_vertical_line(all, x, (int)posh.x
//				% CUBE_SIZE, 2);
//		else
//			draw_vertical_line(all, x, (int)posh.x
//				% CUBE_SIZE, 3);
	}
}

void	ft_cast_ray(t_all *all)
{
	t_vectord	pv;
	t_vectord	ph;
	t_vectordf	distance;
	int			x;

	x = 0;
	all->player->left = all->player->dir - M_PI / 6;
	all->player->right = all->player->dir + M_PI / 6;
	dir_normalize(&all->player->left);
	dir_normalize(&all->player->right);
	while (x < all->res_x)
	{
		all->hits->pos = all->player->pos;
		ph = check_horizontal_lines(all, all->hits->pos, all->player->left);
		pv = check_vertical_lines(all, all->hits->pos, all->player->left);
		distance.x = hypotf(all->hits->pos.x - pv.x, all->hits->pos.y - pv.y);
		distance.y = hypotf(all->hits->pos.x - ph.x, all->hits->pos.y - ph.y);
		check_distance_posv(all, distance, pv, x);
		check_distance_posh(all, distance, ph, x);
		x++;
		all->player->left += M_PI / 3 / all->res_x;
	}
}
