NAME = minishell

CC = gcc

LIBFT = ./libft/libft.a
LIBFT_FLAGS = -L=libft -lft

# SANFLAGS = -fsanitize=address

CFLAGS = -Wall -Wextra -Werror -fcommon -g $(SANFLAGS)

LIBS = -lreadline

INCLUDES = ./includes

# HEADERS = $(INCLUDES)/minishell.h
HEADERS = $(wildcard $(INCLUDES)/*.h)

SRC = main/main.c \
 \
executor/cd_handler.c      executor/run_bin.c       executor/run_export.c \
executor/executor.c        executor/run_builtins.c  executor/run_pwd.c \
executor/export_handler.c  executor/run_cd.c        executor/run_unset.c \
executor/pipe_and_redir.c  executor/run_echo.c \
executor/pipe_handler.c    executor/run_exit.c \
 \
lexer/first_pass.c          lexer/read_line.c        lexer/wordsplit.c \
lexer/first_pass_helpers.c  lexer/string_tokenize.c \
lexer/ft_split2.c           lexer/word_desc.c \
 \
parser/args.c         parser/parse_env.c  parser/redir.c          parser/validity.c \
parser/handle_vars.c  parser/path.c       parser/redir_helpers.c \
parser/parse.c        parser/pipe.c       parser/tokens_insert.c \
 \
utils/commands_free.c  utils/fd_func.c        utils/word_list.c \
utils/itoa2.c          utils/ft_atoi2.c       utils/signal.c \
utils/env_free.c       utils/get_param.c      utils/string_list.c \
utils/error.c          utils/heredoc_subst.c  utils/tokens.c \

SRC := $(addprefix srcs/, $(SRC))

LIBFT_SRC =	ft_atof.c \
			ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_error_exit.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_islower.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_isupper.c \
			ft_itoa.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_split_clear.c \
			ft_ssplit.c \
			ft_str_c_count.c \
			ft_strchr.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strequ.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			get_next_line.c

LIBFT_SRC := $(addprefix libft/, $(LIBFT_SRC))

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

