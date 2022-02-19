# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jblythe <jblythe@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/18 17:10:17 by jblythe           #+#    #+#              #
#    Updated: 2021/10/24 17:21:18 by mgracefo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = TapForLife

CC = clang

HEADER = cub3d.h get_next_line/get_next_line.h

CFLAGS = -O3 -Wall -Werror -Wextra

DFLAGS = -fsanitize=address -Wall -Werror -Wextra

SRCS =	ft_split.c\
        screenshot.c\
        get_next_line/get_next_line.c\
        main.c map_rendering.c\
        get_next_line/get_next_line_utils.c\
        cub3d_utils.c\
        parser.c\
        input.c\
        rendering.c\
        raycasting.c\
        init.c\
        raycasting_error.c\
        movement.c\
        map_parsing.c\
        map_utils.c\
        color_parsing.c\
        kek.c\
        parse_utils.c

MLX = libmlx.a
LIBS = -lmlx -framework OpenGL -framework AppKit
OBJS = ${SRCS:.c=.o}

$(OBS): %.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $< -o $@

$(NAME): $(OBJS) $(MLX) $(HEADER)
	make -C mlx
	cp mlx/$(MLX) .
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(MLX):
	@$(MAKE) -C mlx

all:  $(NAME)

debug:
	$(CC) $(DFLAGS) $(SRCS) -o $(NAME) $(LIBS)

clean:
	@make clean -C mlx
	@rm -f $(OBJS)
	@echo "library cleaned"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(MLX)
	@echo "library full cleaned"

1: all
	@./$(NAME) GameStory/1
play: all
	@./$(NAME) GameStory/1
	@./$(NAME) GameStory/2
	@./$(NAME) GameStory/3
	@./$(NAME) GameStory/4
2: all
	@./$(NAME) GameStory/2
3: all
	@./$(NAME) GameStory/3
4: all
	@./$(NAME) GameStory/4
re: fclean all

.PHONY: re all clean fclean debug 1 2 3 4 play
