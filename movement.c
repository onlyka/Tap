/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:00:50 by jblythe           #+#    #+#             */
/*   Updated: 2021/04/12 18:28:01 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_all *all)
{
	if (all->keys.forward == 1)
	{
			all->player->pos.x += cos(all->player->dir) / CUBE_SIZE * SCALE
				* MOVE_SPEED;
			all->player->pos.y += sin(all->player->dir) / CUBE_SIZE * SCALE
				* MOVE_SPEED;
	}
}

void	move_back(t_all *all)
{
	if (all->keys.back == 1)
	{
			all->player->pos.x -= cos(all->player->dir) / CUBE_SIZE * SCALE
				* MOVE_SPEED;
			all->player->pos.y -= sin(all->player->dir) / CUBE_SIZE * SCALE
				* MOVE_SPEED;
	}
}

void	move_left(t_all *all)
{
	if (all->keys.left == 1)
	{
			all->player->pos.x += sin(all->player->dir) / CUBE_SIZE * SCALE
				* MOVE_SPEED;
			all->player->pos.y -= cos(all->player->dir) / CUBE_SIZE * SCALE
				* MOVE_SPEED;
	}
}

void	move_right(t_all *all)
{
	if (all->keys.right == 1)
	{
			all->player->pos.x -= sin(all->player->dir) / CUBE_SIZE * SCALE
				* MOVE_SPEED;
			all->player->pos.y += cos(all->player->dir) / CUBE_SIZE * SCALE
				* MOVE_SPEED;
	}
}

void	movement(t_all *all)
{
	move_back(all);
	move_forward(all);
	move_left(all);
	move_right(all);
}
