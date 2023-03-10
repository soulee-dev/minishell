NAME = minishell
# CFLAGS = -Wall -Wextra -Werror

SRCS :=
SRCS += pipe.c
SRCS += error.c
SRCS += parser.c
SRCS += env_list.c
SRCS += cmd_list.c
SRCS += here_doc.c
SRCS += builtins1.c
SRCS += builtins2.c
SRCS += minishell.c
SRCS += pipe_utils.c
SRCS += redirection.c
SRCS += file_control.c
SRCS += string_utils.c
SRCS += parser_utils.c
SRCS += string_utils2.c
SRCS += builtin_utils.c
SRCS += env_list_utils.c

LIBFT = ./libft/libft.a

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $? -g3

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $@ $^ -Llibft -lft -lreadline -g3
	@echo Mandatory Compile Complete! 🥳

$(LIBFT):
	make -C ./libft bonus

clean:
	rm -f $(OBJS)
	make clean -C ./libft

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re