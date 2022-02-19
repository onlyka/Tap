/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 19:19:29 by jblythe           #+#    #+#             */
/*   Updated: 2021/10/24 07:21:00 by jblythe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# define SCALE 1
# define HEAL 100
# define CUBE_SIZE 128
# define MOVE_SPEED 300
# define PI_2 6.283188
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_L 123
# define KEY_R 124
# define FLOOR_COLOR 0x366b1b
# define SKY_COLOR 0xf0ca35
# define BORDER_SIZE 50
# define SCREEN_X 1600
# define SCREEN_Y 1000
# define CUB3D_CUB3D_H

typedef struct s_keys{
	int			forward;
	int			back;
	int			left;
	int			right;
	int			a_right;
	int			a_left;
}				t_keys;

typedef struct s_vectord{
	double		x;
	double		y;
}				t_vectord;

typedef struct s_vectorfd{
	double		x;
	double		y;
}				t_vectordf;

typedef struct s_hits{
	t_vectord	pos;
	float		distance;
}				t_hits;

typedef struct s_player{
	t_vectord	pos;
	double		dir;
	float		left;
	float		right;
}				t_player;

typedef struct s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_data;

typedef struct s_sprite {
	int			id;
	t_vectord	pos;
	float		distance;
}				t_sprite;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	void	*img_ptr;
	char	*my_im_d;
	int		bpp;
	int		size_line;
	int		endian;
	char	*pechat;
	char	*word_for_put;
	char	**from_file; //split
	int		len_of_word;
	int		number_of_word; //index
	int		max_word;
	int		max_count;
	int		game_count;
	int		end_game;
	char 	*klava;
	char	*bigklava;
	int		*keys;
	int		shift;
	int		shift_help;
	int		bukva_v_slove;
	void	*texxx;
}	t_vars;

typedef struct s_all{
	char		**map;
	unsigned int	frameCounter;
	unsigned int	lHandCounter;
	unsigned int	rHandCounter;
	int			enemyIndex;
	int			moonIndex;
	int			lHandIndex;
	int			rHandIndex;
	t_vars		*vars;
	int			testLen;
	float		velocity;
	t_player	*player;
	t_data		*img;
	t_sprite	*sprites;
	int			**texture;
	int			flipx;
	int			line_count;
	int			sprites_count;
	int			res_x;
	int			res_y;
	int			border_size;
	char		*sprite_path;
	int			f_color;
	int			c_color;
	t_hits		*hits;
	t_keys		keys;
}				t_all;

void			print_error(t_all *all, char *s);
void			parser(t_all *all, char *path);
void			init(t_all *all, char **split);
int				key_pressing(int key, t_all *all);
void			draw_borders(t_all *all);
int				key_releasing(int key, t_all *all);
int				update(t_all *all);
int				quit(int null);
void			rendering(t_all *all);
void			ft_cast_ray(t_all *all);
void			clear_image(t_all *all);
void			my_mlx_pixel_put(t_all *all, int x, int y, int color);
char			*ft_strdup(char *s1);
void			dir_normalize(float *dir);
char			check_in_array(t_all *all, int x, int y);
void			dir_normalize(float *dir);
void			draw_vertical_line(t_all *all, int x, int posx, int
					id);
int				bmp(t_all *all);
int				ft_strncmp(char *s1, char *s2, int n, int flag);
char			**ft_split(char *s, char c);
int				check_horizontal_error(float dir, t_vectord hit, t_vectord *a,
					int *d);
int				check_vert_error(float dir, t_vectord hit, t_vectord *b,
					int *d);
void			movement(t_all *all);
int				ft_atoi(const char *c);
int				arg_overflow(char *line, int size);
int				get_arg_count(char **line);
int				ft_strncmp(char *s1, char *s2, int n, int flag);
int				create_rgb(int r, int g, int b);
int				map_detected(char *line);
int				search_sprites(const char *s, int c);
int				find_one(t_all *all, int x, int y, char *vector);
int				map_checker(t_all *all);
int				map_parsing(t_all *all, char *path, int j);
void			map_calc(t_all *all, int *line_count, int j, char *path);
int				parse_color(t_all *all, char *line, char symbol);
void			kek(int *i, int *j, char **line);
void			kek2(t_all *all, char **tmp);
void			kek3(char **line, char ***split);
int				open_cub(t_all *all, char *path);
void			free_all_arg(char ***line);
void			path_parsing(t_all *all, char *line, char **f_path, int c);

#endif
