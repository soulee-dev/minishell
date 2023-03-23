CC=gcc
CFLAGS=-Wall -Wextra -Werror
NAME=libftprintf.a
SRCS=ft_printf.c ft_put1.c ft_put2.c
OBJS=$(SRCS:.c=.o)
HEADER=ft_printf.h

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I /ft_printf.h

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

.PHONY: clean fclean re all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all