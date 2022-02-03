SRC = firstfract.c structure.c Mandel.c

NAME = fractol

CC = gcc 

HEADER = fractol.h

LIBX = -I minilib_mms -L minilibx

FLAGS	= -Wall -Wextra -Werror  

OBJ = firstfract.o structure.o Mandel.o


RM = rm -f

all	: ${NAME}

$(NAME): ${OBJ}
		${CC} ${FLAGS} -o ${NAME} $(LIBX) $(SRC) -g -L. -lmlx -lXext -lX11 -lm
clean :
	${RM} ${OBJ}

fclean :	clean
	${RM} ${NAME}

re :	fclean all
