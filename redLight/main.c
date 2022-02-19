#include "head.h"

int	enter_key(int keycode, t_vars *vars)
{
    if (vars->end_game == 1)
        return (0);
    if (keycode == 257 || keycode == 258)
    {
        vars->shift = 1;
        return (0);
    }
    else
    {
        if (vars->shift == 1 && vars->shift_help == 0)
            vars->shift_help++;
        else
        {
            vars->shift_help = 0;
            vars->shift = 0;
        }
    }
	int i = 0;
    while (i < 27)
    {
        if ((vars->bukva_v_slove < vars->len_of_word) && (vars->keys[i] == keycode))
        {
            if ((!vars->shift && vars->klava[i] == vars->from_file[vars->number_of_word][vars->bukva_v_slove]) ||
                (vars->shift == 1 && (vars->bigklava[i] == vars->from_file[vars->number_of_word][vars->bukva_v_slove])))
            {
                vars->game_count++;
                if (vars->shift == 0)
                    vars->pechat[vars->bukva_v_slove] = vars->klava[i];
                else
                    vars->pechat[vars->bukva_v_slove] = vars->bigklava[i];
            //    vars->word_for_put[bukva_v_slove] = ' ';//чтобы удалять строку-образец
                vars->bukva_v_slove++;
                mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ptr, 0, 0);
                    mlx_string_put(vars->mlx, vars->win, 60 + (vars->number_of_word % 2) * 300, 0, 0xcd5c5c, vars->word_for_put);
                mlx_string_put(vars->mlx, vars->win, 58 + (vars->number_of_word % 2) * 300, 1, 0xff7f, vars->pechat);
                if (vars->bukva_v_slove == vars->len_of_word)
                {
                    vars->bukva_v_slove = 0;
                    vars->number_of_word++; 
                    if (vars->number_of_word >vars->max_word - 2)
                    {
                        mlx_string_put(vars->mlx, vars->win, 300, 300, 0xcd5c5c, "POBEDA");
                        vars->end_game = 1;
                        return (0);
                    }
                    vars->len_of_word = strlen(vars->from_file[vars->number_of_word]);//связать со спрайтами
                    free(vars->word_for_put);
                    vars->word_for_put = malloc(sizeof(char)* vars->len_of_word + 1);
                    strlcpy(vars->word_for_put, vars->from_file[vars->number_of_word], vars->len_of_word + 1);
                    mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ptr, 0, 0);
                    mlx_string_put(vars->mlx, vars->win, 60 + (vars->number_of_word % 2) * 300, 0, 0xcd5c5c, vars->word_for_put);
                        free(vars->pechat);
                        vars->pechat = malloc(sizeof(char)* vars->len_of_word + 1);
                        bzero(vars->pechat, vars->len_of_word + 1);
                }
            }
        }
        i++;
    }
    return (0);
}

int	closex(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	ft_close(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

void	all_hooks_mlx(t_vars *vars)
{
	mlx_key_hook(vars->win, ft_close, vars);
	mlx_hook(vars->win, 02, 1L << 0, enter_key, vars);
	mlx_hook(vars->win, 17, 0, closex, vars);
}

int	main(int argc, char **argv)
{
t_vars	vars;
(void)argc;
(void)argv;
vars.number_of_word = 0;
vars.game_count = 0;
vars.max_count = 0;
vars.shift = 0;
vars.shift_help = 0;
vars.bukva_v_slove = 0;
char *klav = "qazwsxedcrfvtgbyhnujmikolp";
char *bigklav = "QAZWSXEDCRFVTGBYHNUJMIKOLP";
int key[26] = {12, 0, 6, 13, 1, 7, 14, 2, 8, 15, 3, 9, 17, 5, 11, 16, 4, 45, 32, 38, 46, 34, 40, 31, 37, 35};
vars.klava = klav;
vars.bigklava = bigklav;
vars.keys = key;
char from_fil[1024];


    int fd;
    int rez;
    if (argc == 2)
        fd = open(argv[1], O_RDONLY);
    else
        fd = open("default", O_RDONLY);
    if (fd == -1)
        closex(&vars);
    rez = read(fd, from_fil, 1023);
    if (rez == -1)
        closex(&vars);
    from_fil[rez] = '\0';
    vars.from_file = ft_split(from_fil, ' ');
    vars.max_word = 0;
    while (vars.from_file[vars.max_word] != '\0')
    {
        for (int i = 0; vars.from_file[vars.max_word][i] != '\0'; i++)
            vars.max_count++;
        vars.max_word++;
    }
    vars.max_count--;
    close(fd);

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, XSIZE, YSIZE, "redLight");
	vars.img_ptr = mlx_new_image(vars.mlx, XSIZE, YSIZE);
    	vars.my_im_d = mlx_get_data_addr(vars.img_ptr, &(vars.bpp),
			&(vars.size_line), &(vars.endian));
    vars.len_of_word = strlen(vars.from_file[vars.number_of_word]);
    vars.pechat = malloc(sizeof(char)* vars.len_of_word + 1);
    vars.word_for_put = malloc(sizeof(char)* vars.len_of_word + 1);
    strlcpy(vars.word_for_put, vars.from_file[vars.number_of_word], vars.len_of_word + 1);
    bzero(vars.pechat, vars.len_of_word + 1);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img_ptr, 0, 0);
    mlx_string_put(vars.mlx, vars.win, 60, 0, 0xcd5c5c, vars.word_for_put);
    all_hooks_mlx(&vars);
    mlx_loop(vars.mlx);
}