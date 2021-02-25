NAME = cub3D

SRC =	cub3d.c utils.c ft_wrmalloc.c libft.c \
		cub.c checkelements.c ft_strtrim.c get_next_line.c islinevalid.c libftstuff.c structstuff.c whatsthemap.c

OBJ = ${SRC:.c=.o}

CC  = gcc

RM  = rm -f

CFLAGS = -I. -g3 -fsanitize=address #-Wall -Wextra -Werror

all:		$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) ${CFLAGS} -L. -lmlx $^ -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:		fclean all