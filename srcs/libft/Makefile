SRCS = ft_strlen.c ft_strncmp.c ft_putstr_fd.c safe_free.c ft_malloc.c \
	ft_strdup.c ft_substr.c ft_memcpy.c ft_strjoin.c free_c_dptr.c ft_split.c \
	ft_strchr.c ft_isalpha.c ft_isnum.c ft_fork.c perror_exit.c ft_isnumstr.c \
	ft_atoi.c ft_getcwd.c ft_strlcpy.c ft_strnstr.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs
RM = rm
RMFLAGS = -f
NAME = libft.a

.PHONY	:	all
all	:	$(NAME)

$(NAME)	:	$(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

.PHONY	:	.c.o
.c.o	:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY	:	clean
clean	:
	$(RM) $(RMFLAGS) $(OBJS)

.PHONY	:	fclean
fclean	:	clean
	$(RM) $(RMFLAGS) $(NAME)

.PHONY	:	re
re	:	fclean all