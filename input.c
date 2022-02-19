/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:51:21 by jblythe           #+#    #+#             */
/*   Updated: 2021/10/24 07:36:59 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	animMagic(t_all *all)
{
	all->frameCounter++;
	if(all->lHandCounter > 0)
		all->lHandCounter--;
	else
		all->lHandIndex = 0;
	if(all->rHandCounter > 0)
		all->rHandCounter--;
	else
		all->rHandIndex = 0;
	all->border_size = BORDER_SIZE + all->frameCounter/4;
	all->enemyIndex = (all->frameCounter / 10) % 2;
	if (all->moonIndex != 21)
		all->moonIndex = 10 + (all->frameCounter / 50) % 12;
	if (all->frameCounter > 600)
		all->vars->end_game = 2;
	return (0);
}

void	dir_normalized(double *dir)
{
	if (*dir >= PI_2)
		*dir -= PI_2;
	if (*dir <= 0)
		*dir += PI_2;
}

int	update(t_all *all)
{
	animMagic(all);
	rendering(all);
	if (all->keys.a_left == 1)
		all->player->dir -= 0.0349066;
	if (all->keys.a_right == 1)
	{
		all->player->dir += 0.0349066;
	}
	dir_normalized(&(all->player->dir));
	movement(all);
	return (0);
}

int	quit(int null)
{
	exit(null);
}
