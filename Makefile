NAME = minishell

CC = clang

LIBFT = ./libft/libft.a
LIBFT_FLAGS = -L=libft -lft

SANFLAGS = -fsanitize=address

CFLAGS = -Wall -Wextra -Werror -fcommon -g $(SANFLAGS)

LIBS = -lreadline

INCLUDES = ./includes

# HEADERS = $(INCLUDES)/minishell.h
HEADERS = $(wildcard $(INCLUDES)/*.h)

SRC = $(wildcard ./srcs/*/*.c)
LIBFT_SRC = $(wildcard ./libft/*.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ): %.o: %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -I $(INCLUDES) -o $@

$(NAME): $(LIBFT) $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) $(LIBS) -o $(NAME)

$(LIBFT): $(LIBFT_SRC)
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

debug: CFLAGS += -D DEBUG=1
debug: run

run: $(NAME)
	@ ASAN_OPTIONS=detect_leaks=1 LSAN_OPTIONS=suppressions=.readline.supp ./$(NAME)

norm: 
	norminette $(SRC)
	norminette $(INCLUDES)

.PHONY: all clean fclean re norm

