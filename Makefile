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
SRCS += parser_utils2.c
SRCS += parser_utils3.c
SRCS += string_utils2.c
SRCS += string_utils3.c
SRCS += builtin_utils.c
SRCS += env_list_utils.c

LIBFT = ./libft/libft.a
FT_PRINTF = ./ft_printf/libftprintf.a

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(FT_PRINTF) $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $? -g3

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) -o $@ $^ -Llibft -lft -Lft_printf -lftprintf -lreadline -g3
	@echo Mandatory Compile Complete! 🥳

$(LIBFT):
	make -C ./libft bonus

$(FT_PRINTF):
	make -C ./ft_printf

clean:
	rm -f $(OBJS)
	make clean -C ./libft
	make clean -C ./ft_printf

fclean: clean
	make fclean -C ./libft
	make fclean -C ./ft_printf
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re