SRC = Mandel.c firstfract.c

CC = gcc

HEADER = libftprintf.h

OBJ = $(SRC:.c=.o)

NAME = libftprintf.a

RM = rm -f

LIBC = ar -rc

CFLAGS	= -Wall -Wextra -Werror

%.o : %.c
	$(CC) ${CFLAGS} -I. -o $@ -c $?

${NAME} : $(OBJ)
	${LIBC} ${NAME} ${OBJ}

all :	${NAME} 

clean :
	${RM} ${OBJ}

fclean :	clean
	${RM} ${NAME}

re :	fclean all
