SRC = fract-ol.c julia.c others.c input.c mandelbrot.c burningship.c

OBJS = $(SRC:.c=.o)

RM = rm -f

NAME = fractol

LMLX = mlx/libmlx.a

gcc= gcc -Wall -Werror -Wextra

all : ${LMLX} $(NAME)

${LMLX}:
		make -C mlx/ all

.c.o:
		$(gcc) -Lmlx/ -lmlx -L/usr/lib/ -lXext -lX11 -lm -I ./ -I ./mlx/ -c $< -o $(<:.c=.o)

$(NAME) :	$(OBJS)
		$(gcc) ${OBJS} -Lmlx/ -lmlx -L/usr/lib/ -lXext -lX11 -lm -I./ -I./mlx/ -o ${NAME}

clean :
		$(RM) $(OBJS)
		make -C mlx/ clean

fclean :	clean
				$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
