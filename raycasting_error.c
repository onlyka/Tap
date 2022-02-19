/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:13:43 by jblythe           #+#    #+#             */
/*   Updated: 2021/04/08 21:28:44 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_horizontal_error(float dir, t_vectord hit, t_vectord *a, int *d)
{
	if (dir < M_PI)
	{
		*d = 1;
		(*a).y = (int)(hit.y / CUBE_SIZE) *CUBE_SIZE + CUBE_SIZE;
	}
	else if (dir > M_PI)
	{
		(*a).y = (int)(hit.y / CUBE_SIZE) *(CUBE_SIZE) + 1 / CUBE_SIZE;
		*d = -1;
	}
	else
		return (1);
	(*a).x = hit.x - (hit.y - (*a).y) / tan(dir);
	return (0);
}

int	check_vert_error(float dir, t_vectord hit, t_vectord *b, int *d)
{
	if (dir < M_PI / 2 || dir > 3 * M_PI / 2)
	{
		*d = -1;
		(*b).x = (int)(hit.x / CUBE_SIZE) *CUBE_SIZE + CUBE_SIZE;
	}
	else if (dir > M_PI / 2 || dir < 3 * M_PI / 2)
	{
		*d = 1;
		(*b).x = (int)(hit.x / CUBE_SIZE) *(CUBE_SIZE) + 1 / CUBE_SIZE;
	}
	else
		return (1);
	(*b).y = hit.y - (hit.x - (*b).x) * tan(dir);
	return (0);
}
