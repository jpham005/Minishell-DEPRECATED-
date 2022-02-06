SRCS_DIR := srcs
ENVP_DIR := $(SRCS_DIR)/envp
UTILS_DIR := $(SRCS_DIR)/utils

INCLUDE := include

READLINE_DIR := $(shell brew --prefix readline)
READLINE_INCLUDE := $(READLINE_DIR)/include
READLINE_LIB := $(READLINE_DIR)/lib

ENVP_SRCS := manage_envp.c envp_util.c
ENVP_SRCS := $(addprefix $(ENVP_DIR)/, $(ENVP_SRCS))
UTILS_SRCS := convert_exit_status.c exit_manage.c print_intro.c
UTILS_SRCS := $(addprefix $(UTILS_DIR)/, $(UTILS_SRCS))
MAIN_SRCS := main.c set_terminal_state.c
MAIN_SRCS := $(addprefix $(SRCS_DIR)/, $(MAIN_SRCS))

LIBFT_DIR := $(SRCS_DIR)/libft
LIBFT := $(LIBFT_DIR)/libft.a

CC := gcc
CFALGS := -g
NAME := minishell
SRCS := $(ENVP_SRCS) $(UTILS_SRCS) $(MAIN_SRCS)
OBJS := $(SRCS:.c=.o)
RM := rm
RMFLAGS := -f

.PHONY	:	all
all	:	$(NAME)

$(NAME)	:	$(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT) $^ -L$(READLINE_LIB) -lreadline -lhistory -o $@

$(LIBFT)	:
	cd $(LIBFT_DIR); make all

.PHONY	:	.c.o
.c.o	:
	$(CC) $(CFLAGS) -I$(READLINE_INCLUDE) -I$(INCLUDE) -I$(LIBFT_DIR) \
	-c $< -o $@

.PHONY	:	clean
clean	:
	$(RM) $(RMFLAGS) $(OBJS)
	cd $(LIBFT_DIR); make clean

.PHONY	:	fclean
fclean	:	clean
	$(RM) $(RMFLAGS) $(NAME) $(LIBFT)

.PHONY	:	re
re	:	fclean all