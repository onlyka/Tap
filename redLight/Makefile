
NAME		= redLight

SRCS = main.c\
		ft_split.c

HEAD		= head.h
OBJS		= $(SRCS:.c=.o)

CC		= gcc

RM		= rm -f

CFLAGS		= -Wall -Werror -Wextra

%.o:	%.c
		$(CC) $(CFLAGS) -Imlx -c $(@:.o=.c) -o $@

$(NAME):	 $(OBJS) 
		$(CC) $(CFLAGS) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(OBJS):	$(HEAD)


all:		$(NAME)
clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean	all

.PHONY:		all clean fclean re