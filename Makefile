NAME = cub3D

CC = gcc

CFLAGS =  -Wall -Wextra -Werror #-fsanitize=address -g3

SRC =	main.c\
		parsing/parsing.c\
		parsing/free.c\
		parsing/get_next_line_utils.c\
		parsing/get_next_line.c\
		parsing/libft/ft_split.c\
		parsing/libft/libft_utils.c\
		parsing/init_vars.c\
		parsing/textures_check.c\
		parsing/textures_utils.c\
		parsing/extention.c\
		parsing/invalid_character.c\
		parsing/player_check.c\
		parsing/valid_path.c\
		execution/map2D.c\
		execution/init.c\
		execution/utils.c\
		execution/drawing_1.c\
		execution/drawing_2.c\
		execution/hook.c\
		execution/raycasting.c\
		execution/drawing_utils.c\
		execution/map_collision.c\
		execution/init_textures.c\
		execution/raycasting_utils1.c\
		execution/raycasting_utils2.c\

OBJ = $(SRC:.c=.o)

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) -lmlx -framework OpenGL -framework AppKit $(CFLAGS) $(OBJ) -o $(NAME)

clean :
		$(RM) $(OBJ)

fclean : clean
			$(RM) $(NAME)

re : fclean all
