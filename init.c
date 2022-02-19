/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:51:12 by jblythe           #+#    #+#             */
/*   Updated: 2021/10/24 04:41:21 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_image(t_all *all, char *path, int **texture, t_data *img)
{
	img->img = mlx_xpm_file_to_image(all->vars->mlx, path,
			&(img->width), &(img->height));
	if (img->img == NULL)
		print_error(all, "Not valid texture path");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	*texture = (int *)img->addr;
}

void	load_textures(t_all *all)
{
	t_data	img;

	load_image(all, "Sprites/Enemy1.xpm", &(all->texture[0]), &img);
	load_image(all, "Sprites/Enemy2.xpm", &(all->texture[1]), &img);
	load_image(all, "Sprites/Enemy3.xpm", &(all->texture[2]), &img);
	load_image(all, "Sprites/Enemy4.xpm", &(all->texture[3]), &img);
	load_image(all, "Sprites/hands1.xpm", &(all->texture[4]), &img);
	load_image(all, "Sprites/hands2.xpm", &(all->texture[5]), &img);
	load_image(all, "Sprites/hands3.xpm", &(all->texture[6]), &img);
	load_image(all, "Sprites/hands4.xpm", &(all->texture[7]), &img);
	load_image(all, "Sprites/hands5.xpm", &(all->texture[8]), &img);
	load_image(all, "Sprites/hands6.xpm", &(all->texture[9]), &img);
	load_image(all, "Sprites/moon1.xpm", &(all->texture[10]), &img);
	load_image(all, "Sprites/moon2.xpm", &(all->texture[11]), &img);
	load_image(all, "Sprites/moon3.xpm", &(all->texture[12]), &img);
	load_image(all, "Sprites/moon4.xpm", &(all->texture[13]), &img);
	load_image(all, "Sprites/moon5.xpm", &(all->texture[14]), &img);
	load_image(all, "Sprites/moon6.xpm", &(all->texture[15]), &img);
	load_image(all, "Sprites/moon7.xpm", &(all->texture[16]), &img);
	load_image(all, "Sprites/moon8.xpm", &(all->texture[17]), &img);
	load_image(all, "Sprites/moon9.xpm", &(all->texture[18]), &img);
	load_image(all, "Sprites/moon10.xpm", &(all->texture[19]), &img);
	load_image(all, "Sprites/moon11.xpm", &(all->texture[20]), &img);
	load_image(all, "Sprites/moon12.xpm", &(all->texture[21]), &img);
}


void	init(t_all *all, char **split)
{
	split = 0x0;
	load_textures(all);
	all->player->dir = M_PI/2;
	all->sprites_count = all->vars->max_word - 1;
	all->sprites = malloc(all->sprites_count * sizeof(t_sprite));
	for (int i = 0; i < all->sprites_count; i++)
	{
		if (i > 0)
		{
			all->sprites[i].pos.x = all->sprites[i - 1].pos.x +cos(ft_strlen
					(all->vars->from_file[i]) / M_PI) * ft_strlen
					(all->vars->from_file[i]) * CUBE_SIZE * 2;
			all->sprites[i].pos.y = all->sprites[i - 1].pos.y + sin(ft_strlen
					(all->vars->from_file[i]) / M_PI) * ft_strlen
					(all->vars->from_file[i]) * CUBE_SIZE * 2;
		}
		else
		{
			all->sprites[i].pos.x = cos(ft_strlen(all->vars->from_file[i]) / M_PI) * ft_strlen
					(all->vars->from_file[i]) * CUBE_SIZE * 2;
			all->sprites[i].pos.y = sin(ft_strlen(all->vars->from_file[i]) / M_PI) * ft_strlen
					(all->vars->from_file[i]) * CUBE_SIZE * 2;
		}
	}
}
