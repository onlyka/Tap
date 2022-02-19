#ifndef _HEAD_H_
# define _HEAD_H_

# define XSIZE 600
# define YSIZE 600
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>

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
	char	**from_file;
	int		len_of_word;
	int		number_of_word;
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
}	t_vars;

void	ft_mandel(t_vars *vars);
char	**ft_split(char const *s, char c);
#endif