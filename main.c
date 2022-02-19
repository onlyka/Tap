/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:19:10 by jblythe           #+#    #+#             */
/*   Updated: 2021/10/24 07:19:18 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cub3d.h"
#include <string.h>

void	print_error(t_all *all, char *s)
{
	printf("Error\n%s\n", s);
	if (all->player != NULL)
		free(all->player);
	if (all->hits != NULL)
		free(all->hits);
	if (all->vars != NULL)
		free(all->vars);
	if (all->texture[0] != NULL)
		free(all->texture[0]);
	if (all->texture[1] != NULL)
		free(all->texture[1]);
	if (all->texture[2] != NULL)
		free(all->texture[2]);
	if (all->texture[3] != NULL)
		free(all->texture[3]);
	if (all->texture[4] != NULL)
		free(all->texture[4]);
	if (all->texture)
		free(all->texture);
	quit(0);
}

void	three_arg(t_all *all, char **argv, int argc)
{
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", ft_strlen(argv[2]), 0) == 0)
			bmp(all);
		else
			print_error(all, "Wrong argument");
		quit(0);
	}
}

void	initial_variables(t_all *all)
{
	all->res_x = SCREEN_X;
	all->res_y = SCREEN_Y;
	all->enemyIndex = 0;
	all->moonIndex = 0;
	all->lHandIndex = 0;
	all->rHandIndex = 0;
	all->lHandCounter = 0;
	all->rHandCounter = 0;
//	all->enemyCounter = 0;
	all->sprite_path = NULL;
	all->hits = NULL;
	all->c_color = SKY_COLOR;
	all->f_color = FLOOR_COLOR;
	all->keys.forward = 0;
	all->keys.back = 0;
	all->keys.left = 0;
	all->keys.right = 0;
	all->keys.a_right = 0;
	all->keys.a_left = 0;
	all->border_size = BORDER_SIZE;
	all->player = malloc(sizeof(t_player));
	all->player->pos.x = 0;
	all->player->pos.y = 0;
	all->player->dir = M_PI/2 - 1;
	all->texture = malloc(sizeof(int *) * 22);
	all->vars = malloc(sizeof(t_vars));
	all->vars->end_game = 0;
	all->vars->keys = malloc(sizeof(int) * 27);
	all->testLen = 0;
	all->texture[0] = NULL;
	all->texture[1] = NULL;
	all->texture[2] = NULL;
	all->texture[3] = NULL;
	all->texture[4] = NULL;
}

void moving(t_all *all)
{
	int i = all->vars->number_of_word;
	double ax = all->player->pos.x;
	double ay = all->player->pos.y;
	double bx = all->sprites[all->sprites_count - i - 1].pos.x;
	double by = all->sprites[all->sprites_count - i - 1].pos.y;

	if (all->testLen > 0)
	{
		all->player->dir = atan2(by - ay, bx - ax);
		all->player->pos.x += cos(atan2(by - ay, bx - ax)) * all->velocity;
		all->player->pos.y += sin(atan2(by - ay, bx - ax)) * all->velocity;
		all->testLen--;
	}
	else
	{
		all->player->dir = atan2(by - ay, bx - ax);
		all->testLen = all->vars->len_of_word; //current string
		all->velocity = sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by)) /
				(float)all->testLen -1;
		all->player->pos.x += cos(atan2(by - ay, bx - ax)) * all->velocity;
		all->player->pos.y += sin(atan2(by - ay, bx - ax)) * all->velocity;
	}

}

void ChangeHand(t_all *all, int i)
{
	int index = (i/3)%27;
	if(i == 26)
	{
		all->rHandCounter = 10;
		all->lHandIndex = 1;
		all->lHandCounter = 0;
	}
	else if (index >= 5)
	{
		all->lHandCounter = 10;
		all->lHandIndex = index + 1 - 5;
	}
	else
	{
		all->rHandCounter = 10;
		all->rHandIndex = 5 - index;
	}
}

int	enter_key(int keycode, t_all *all)
{
	if (keycode == 53)
		exit(0);
	if (all->vars->end_game == 1)
		return (0);
	if (keycode == 257 || keycode == 258)
	{
		all->vars->shift = 1;
		return (0);
	}
	else
	{
		if (all->vars->shift == 1 && all->vars->shift_help == 0)
			all->vars->shift_help++;
		else
		{
			all->vars->shift_help = 0;
			all->vars->shift = 0;
		}
	}
	int i = 0;
	while (i < 27)
	{
		if ((all->vars->bukva_v_slove < all->vars->len_of_word) &&
		(all->vars->keys[i] == keycode))
		{
			ChangeHand(all, i);
			if ((!all->vars->shift && all->vars->klava[i] == all->vars->from_file[all->vars->number_of_word][all->vars->bukva_v_slove]) ||
				(all->vars->shift == 1 && (all->vars->bigklava[i] == all->vars->from_file[all->vars->number_of_word][all->vars->bukva_v_slove])))
			{
				all->vars->game_count++;
				if (all->vars->shift == 0)
					all->vars->pechat[all->vars->bukva_v_slove] = all->vars->klava[i];
				else
					all->vars->pechat[all->vars->bukva_v_slove] = all->vars->bigklava[i];
				all->vars->bukva_v_slove++;
				moving(all);
				//            mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->img->img, 0, 0);
				/* функция для перемещения*/
				//
				if (all->vars->bukva_v_slove == all->vars->len_of_word)
				{
					all->vars->bukva_v_slove = 0;
					all->frameCounter -= HEAL % all->frameCounter;
					all->vars->number_of_word++;
					if (all->vars->number_of_word > all->vars->max_word - 2)
					{
						//             mlx_string_put(all->vars->mlx, all->vars->win, 300, 300, 0xcd5c5c, "POBEDA");
						all->vars->end_game = 1;
						return (0);
					}
					all->vars->len_of_word = strlen(all->vars->from_file[all->vars->number_of_word]);//связать со спрайтами
					free(all->vars->word_for_put);
					all->vars->word_for_put = malloc(sizeof(char)* all->vars->len_of_word + 1);
					strlcpy(all->vars->word_for_put, all->vars->from_file[all->vars->number_of_word], all->vars->len_of_word + 1);
					free(all->vars->pechat);
					all->vars->pechat = malloc(sizeof(char) * all->vars->len_of_word + 1);
					bzero(all->vars->pechat, all->vars->len_of_word + 1);
				}
			}
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	all;
	t_data	img;
	/*add*/
	initial_variables(&all);
	all.vars->number_of_word = 0;
	all.vars->game_count = 0;
	all.vars->max_count = 0;
	all.vars->shift = 0;
	all.vars->shift_help = 0;
	all.vars->bukva_v_slove = 0;
	char *klav = "qazwsxedcrfvtgbyhnujmikolp";
	char *bigklav = "QAZWSXEDCRFVTGBYHNUJMIKOLP";
	int key[26] = {12, 0, 6, 13, 1, 7, 14, 2, 8, 15, 3, 9, 17, 5, 11, 16, 4, 45, 32, 38, 46, 34, 40, 31, 37, 35};
	all.vars->klava = klav;
	all.vars->bigklava = bigklav;
	for (int i = 0; i < 27; i++)
		all.vars->keys[i] = key[i];
	char from_fil[1024];
	int fd;
	int rez;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
	}
	else if (argc == 1)
	{
		fd = open("default", O_RDONLY);
	}
	else
		exit(1);
	if (fd == -1)
		exit(1);
	rez = read(fd, from_fil, 1023);
	if (rez == -1)
		exit(1);
	from_fil[rez] = '\0';
	all.vars->from_file = ft_split(from_fil, ' ');
	all.vars->max_word = 0;
	while (all.vars->from_file[all.vars->max_word] != '\0')
	{
		for (int i = 0; all.vars->from_file[all.vars->max_word][i] != '\0'; i++)
			all.vars->max_count++;
		all.vars->max_word++;
	}
	all.vars->max_count--;
	close(fd);
	all.vars->len_of_word = strlen(all.vars->from_file[all.vars->number_of_word]);
	all.vars->pechat = malloc(sizeof(char)* all.vars->len_of_word + 1);
	all.vars->word_for_put = malloc(sizeof(char)* all.vars->len_of_word + 1);
	strlcpy(all.vars->word_for_put, all.vars->from_file[all.vars->number_of_word], all.vars->len_of_word + 1);
	bzero(all.vars->pechat, all.vars->len_of_word + 1);
	/*end*/


	all.vars->mlx = mlx_init();
	init(&all, all.vars->from_file); //здесь изменил
	all.hits = malloc(sizeof(t_hits) * all.res_x);
	all.vars->win = mlx_new_window(all.vars->mlx, all.res_x, all.res_y,
								   "redLight");
	all.img = &img;
	img.img = mlx_new_image(all.vars->mlx, all.res_x, all.res_y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
								 &img.line_length, &img.endian);
	int y;
	int x= 10;
	y = 10;
	all.vars->texxx = mlx_xpm_file_to_image(all.vars->mlx, "Sprites/sneg.xpm",
											&x,  &y);
	rendering(&all);
	three_arg(&all, argv, argc);
	mlx_loop_hook(all.vars->mlx, &update, &all);
	//mlx_hook(all.vars->win, 2, 1L << 0, &key_pressing, &all);
	//mlx_hook(all.vars->win, 3, 1L << 0, &key_releasing, &all);

	/*add*/
	mlx_hook(all.vars->win, 02, 1L << 0, enter_key, &all);
	mlx_hook(all.vars->win, 17, 1L << 17, quit, 0);
	mlx_put_image_to_window(all.vars->mlx, all.vars->win, all.img->img, 0, 0);
	mlx_string_put(all.vars->mlx, all.vars->win, 60, 0, 0x1111FF,
				   all.vars->word_for_put);
	/*end*/
	mlx_loop(all.vars->mlx);
}
