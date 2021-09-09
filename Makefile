
NAME = minishell

CC = gcc

LIBFT= ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror -g

OFLAGS = -O2

INCLUDES = ./includes

HEADERS = ./includes/minishell.h \

SRC =		srcs/main.c					\
			srcs/read_line.c					\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -o $@

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(OFLAGS) $(CFLAGS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C ./libft

clean:
	$(RM) $(OBJ)
	make clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./libft

re: fclean all

norm: 
	norminette $(SRC)
	norminette $(INCLUDES)

.PHONY: all clean fclean re

