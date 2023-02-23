CC=cc
CFLAGS=-Wall -Wextra -Werror
NAME=libft.a
SRCS=ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUS_SRCS :=
BONUS_SRCS += ft_lstnew_bonus.c
BONUS_SRCS += ft_lstadd_front_bonus.c
BONUS_SRCS += ft_lstsize_bonus.c
BONUS_SRCS += ft_lstlast_bonus.c
BONUS_SRCS += ft_lstadd_back_bonus.c
BONUS_SRCS += ft_lstdelone_bonus.c
BONUS_SRCS += ft_lstclear_bonus.c
BONUS_SRCS += ft_lstiter_bonus.c
BONUS_SRCS += ft_lstmap_bonus.c

OBJS=$(SRCS:.c=.o)
BONUS_OBJS=$(BONUS_SRCS:.c=.o)
ALL_SRCS = $(SRCS) $(BONUS_SRCS)
ALL_OBJS = $(OBJS) $(BONUS_OBJS)

define object_goals
$(call $(if $(filter bonus, $(MAKECMDGOALS)), ALL_OBJS, OBJS))
endef

all: $(NAME)

.PHONY: bonus clean fclean all re

%.o: %.c
	@$(CC) $(CFLAGS) -c $?

$(NAME): $(object_goals)
	@ar rscu $(NAME) $(object_goals)

bonus: $(NAME)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all
