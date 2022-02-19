/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:51:28 by jblythe           #+#    #+#             */
/*   Updated: 2021/10/24 07:56:38 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_nbrlen(long long n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	ft_putnbr_stock(long n, char *str, int *i)
{
	if (n > 9)
	{
		ft_putnbr_stock(n / 10, str, i);
		ft_putnbr_stock(n % 10, str, i);
	}
	else
		str[(*i)++] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nbr;

	nbr = n;
	str = malloc(sizeof(char) * (ft_nbrlen(nbr) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (nbr < 0)
	{
		str[i++] = '-';
		nbr *= -1;
	}
	ft_putnbr_stock(nbr, str, &i);
	str[i] = '\0';
	return (str);
}

void	swap(t_sprite *value1, t_sprite *value2)
{

	t_sprite	tmp;

	tmp = *value1;
	*value1 = *value2;
	*value2 = tmp;

}

void	bubble_sort(t_all *all, t_sprite *values)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i + 1 < all->sprites_count)
	{
		while (j + 1 < all->sprites_count - i)
		{
			if (values[j + 1].distance > values[j].distance)
				swap(&values[j], &values[j + 1]);
			j++;
		}
		i++;
	}
}

void	sorting(t_all *all, int h, int v, int s)
{
	int	i;
	int	j;
	int	sprite_size;

	sprite_size = CUBE_SIZE * all->res_y / all->sprites[s].distance;
	i = -1;
	while (++i < sprite_size)
	{
		if (!(h + i < -all->res_x / 2 || h + i >= all->res_x / 2))
		{
//			if (all->hits[all->res_x / 2 + h + i].distance
//				< all->sprites[s].distance)
//				continue ;
			j = -1;
			while (++j < sprite_size)
			{
				if (!(v + j < 0 || v + j >= all->res_y))
				{
					my_mlx_pixel_put(all, all->res_x / 2 + h + i,
									 v + j, all->texture[all->enemyIndex][(j *
									 127 / sprite_size * 128) + i * 127 /
									 sprite_size]);
				}
			}
		}
	}
}

void	spritering(t_all *all)
{
	float	sprite_dir;
	int		sprite_size;
	int		h_offset;
	int		v_offset;
	int		s;

	s = -1;
	while (++s < all->sprites_count)
	{
		sprite_dir = atan2(all->sprites[s].pos.y - all->player->pos.y,
						   all->sprites[s].pos.x - all->player->pos.x);
		while (sprite_dir - all->player->dir > M_PI)
			sprite_dir -= 2 * M_PI;
		while (sprite_dir - all->player->dir < -M_PI)
			sprite_dir += 2 * M_PI;
		sprite_size = CUBE_SIZE * all->res_y / all->sprites[s].distance;
		h_offset = ((sprite_dir - all->player->dir) * M_PI) * (all->res_x / 2)
				   / (M_PI / 2) - sprite_size / 2;
		v_offset = all->res_y / 2 - sprite_size / 2;
		sorting(all, h_offset, v_offset, s);
	}
}

void	draw_invert_texture(t_all *all, int id, int distanceX, int distanceY,
						   int size)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < CUBE_SIZE * size)
	{
		while (y < CUBE_SIZE * size)
		{
			my_mlx_pixel_put(all, distanceX - x - 1 + CUBE_SIZE * size, y
					+ distanceY, all->texture[id][y / size * CUBE_SIZE + x / size]);
			y++;
		}
		y = 0;
		x++;
	}
}

void	draw_texture(t_all *all, int id, int distanceX, int distanceY, int size)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < CUBE_SIZE * size)
	{
		while (y < CUBE_SIZE * size)
		{
			my_mlx_pixel_put(all, x + distanceX, y + distanceY,
							 all->texture[id][y / size * CUBE_SIZE + x / size]);
			y++;
		}
		y = 0;
		x++;
	}
}

void draw_moon(t_all *all, int id)
{
	if (id > 18)
		draw_texture(all, id, 800 -512, -12, 8);
	else
		draw_texture(all, id, 800 -256 -128, 500 -256 -128, 6);
}

void draw_hands(t_all *all)
{
	draw_texture(all, 4+ all->lHandIndex,
				 1000 - all->lHandCounter, SCREEN_Y/2 - all->lHandCounter, 4);
	draw_invert_texture(all, 4 + all->rHandIndex,
						100 + all->rHandCounter, SCREEN_Y/2-
						all->rHandCounter, 4);
}

void	rendering(t_all *all)
{
	int	s;

	s = -1;
	clear_image(all);
	while (++s < all->sprites_count)
		all->sprites[s].distance = sqrt(pow(all->player->pos.x
											- all->sprites[s].pos.x, 2) + pow(all->player->pos.y
																			  - all->sprites[s].pos.y, 2));
	bubble_sort(all, all->sprites);
	if (all->moonIndex < 18)
		draw_moon(all, all->moonIndex);
	spritering(all);
	draw_borders(all);
	if (all->moonIndex >= 18)
		draw_moon(all, all->moonIndex);
	draw_hands(all);
	mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->img->img, 0,
							0);
	if (all->vars->end_game == 0)
	{
		mlx_string_put(all->vars->mlx, all->vars->win, 221 +
		(all->vars->number_of_word % 2) * 900, 201, 0x000000, all->vars->word_for_put);
		mlx_string_put(all->vars->mlx, all->vars->win, 220 +
		(all->vars->number_of_word % 2) * 900, 200, 0x000000, all->vars->word_for_put);
		mlx_string_put(all->vars->mlx, all->vars->win, 220 +
		(all->vars->number_of_word % 2) * 900, 200, 0xFF0000, all->vars->pechat);
	}
	else if (all->vars->end_game == 1)
	{
		int x = 0;
		int y = 0;
		while(y < SCREEN_Y)
		{
			while(x < SCREEN_X)
			{
				my_mlx_pixel_put(all, x, y, 0x321d47);
				x++;
			}
			x = 0;
			y++;
		}

		mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->img->img, 0,
								0);
		mlx_string_put(all->vars->mlx, all->vars->win, SCREEN_X / 2 + 1 -20,
					   SCREEN_Y / 2 + 1, 0x0011FF, "WINNER");
		mlx_string_put(all->vars->mlx, all->vars->win, SCREEN_X / 2 - 20,
					   SCREEN_Y / 2 + 1, 0xFF0000, "WINNER");
		mlx_string_put(all->vars->mlx, all->vars->win, SCREEN_X / 2, SCREEN_Y
		/ 2 +  21, 0x0011FF, ft_itoa(all->vars->max_count));
		mlx_string_put(all->vars->mlx, all->vars->win, SCREEN_X / 2, SCREEN_Y
		/ 2 + 20, 0xFF0000, ft_itoa(all->vars->max_count));
	}
	else
	{
		int x = 0;
		int y = 0;
		while(y < SCREEN_Y)
		{
			while(x < SCREEN_X)
			{
				my_mlx_pixel_put(all, x, y, 0x321d47);
				x++;
			}
			x = 0;
			y++;
		}

		mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->img->img, 0,
								0);
		char *ahah = ft_strdup
				("AHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHA");

		for(int i = 0; i < 50; i++)
		{
				mlx_string_put(all->vars->mlx, all->vars->win,
							   all->frameCounter %10 *10 - 100, i * 20,
							   0x0011FF, ahah);
		}

		mlx_string_put(all->vars->mlx, all->vars->win, SCREEN_X/2-20, SCREEN_Y
		/ 2,
					   0xFF0000, "LOOSER");
	}
//			mlx_string_put(all->vars->mlx, all->vars->win, 60, 0, 0x1111FF,
//				   all->vars->word_for_put);
}
