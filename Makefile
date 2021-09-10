NAME = minishell

CC = clang

LIBFT = ./libft/libft.a
LIBFT_FLAGS = -L=libft -lft

# SANFLAGS = -fsanitize=address

CFLAGS = -Wall -Wextra -Werror -g $(SANFLAGS)

LIBS = -lreadline

INCLUDES = ./includes

HEADERS = $(INCLUDES)/minishell.h

SRC = $(wildcard ./srcs/*/*.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ): %.o: %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -o $@

$(NAME): $(LIBFT) $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C ./libft

re:
	$(MAKE) fclean
	$(MAKE) all

norm: 
	norminette $(SRC)
	norminette $(INCLUDES)

.PHONY: all clean fclean re

