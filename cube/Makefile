NAME = cube

CC = gcc

CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3

SRC =	main.c\
		parsing/parsing.c\
		parsing/free.c\
		parsing/test.c\
		parsing/ft_atoi.c\
		parsing/get_next_line_utils.c\
		parsing/get_next_line.c\
		parsing/libft/ft_split.c\
		parsing/libft/libft_utils.c\

OBJ = $(SRC:.c=.o)

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC)  $(CFLAGS) $(OBJ) -o $(NAME)

clean :
		$(RM) $(OBJ)

fclean : clean
			$(RM) $(NAME)

re : fclean all
 