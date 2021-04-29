NAME = cub3D

SRC =	init/main.c \
		init/init_mlx.c \
		init/init_textures.c \
		utils/ft_wrmalloc.c \
		parsing/checkelements.c \
		parsing/cub.c \
		parsing/ft_strtrim.c \
		parsing/get_next_line.c \
		parsing/islinevalid.c \
		parsing/libftstuff.c \
		parsing/structstuff.c \
		parsing/whatsthemap.c \
		parsing/skynfloorcolor.c \
		parsing/spacenplayerpos.c \
		parsing/libft.c \
		parsing/ft_substr.c \
		parsing/listes.c \
		parsing/getlenmax.c \
		save/save.c \
		hook/hook.c \
		sprites/sprites.c \
		sprites/spr_sort.c \
		printer/printer.c \
		raycasting/raycasting.c

OBJ = ${SRC:.c=.o}

CC  = gcc

RM  = rm -f

CFLAGS = -I. -O3 -Wall -Wextra -Werror -g3 #-fsanitize=address #-Wall -Wextra -Werror

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
