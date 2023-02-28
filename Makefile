SRC = fract-ol.c

OBJS = $(SRC:.c=.o)

RM = rm -f

NAME = fract-ol
LMLX = mlx/libmlx.a

all : ${LMLX} $(NAME)

${LMLX}:
		make -C mlx/ all

.c.o:
		gcc -Wall -Werror -Wextra -Lmlx/ -lmlx -L/usr/lib/ -lXext -lX11 -lm -I ./ -I ./mlx/ -c $< -o $(<:.c=.o)

$(NAME) :	$(OBJS)
		gcc -Wall -Werror -Wextra ${OBJS} -Lmlx/ -lmlx -L/usr/lib/ -lXext -lX11 -lm -I./ -I./mlx/ -o ${NAME}

clean :
		$(RM) $(OBJS)
		make -C mlx/ clean

fclean :	clean
				$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
