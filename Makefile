# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaham <jaham@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 20:45:33 by jaham             #+#    #+#              #
#    Updated: 2022/02/16 20:45:56 by jaham            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR := srcs
BUILT_IN_DIR := $(SRCS_DIR)/built_in
ENVP_DIR := $(SRCS_DIR)/envp
UTILS_DIR := $(SRCS_DIR)/utils
TERMINAL_DIR := $(SRCS_DIR)/terminal

INCLUDE := include
INCLUDE_FILES := built_in.h color.h envp.h terminal.h main.h utils.h exec.h
INCLUDE_FILES := $(addprefix $(INCLUDE)/, $(INCLUDE_FILES))

READLINE_DIR := $(shell brew --prefix readline)
READLINE_INCLUDE := $(READLINE_DIR)/include
READLINE_LIB := $(READLINE_DIR)/lib

BUILT_IN_SRCS := export.c unset.c env.c pwd.c exit.c cd.c cd_util.c echo.c
BUILT_IN_SRCS := $(addprefix $(BUILT_IN_DIR)/, $(BUILT_IN_SRCS))
ENVP_SRCS := init_destroy.c util.c print.c tool.c
ENVP_SRCS := $(addprefix $(ENVP_DIR)/, $(ENVP_SRCS))
UTILS_SRCS := exit_manage.c print_intro.c
UTILS_SRCS := $(addprefix $(UTILS_DIR)/, $(UTILS_SRCS))
TERMINAL_SRCS := check_default_state.c set_state.c signal_handler.c init.c
TERMINAL_SRCS := $(addprefix $(TERMINAL_DIR)/, $(TERMINAL_SRCS))
MAIN_SRCS := main.c
MAIN_SRCS := $(addprefix $(SRCS_DIR)/, $(MAIN_SRCS))

LIBFT_DIR := $(SRCS_DIR)/libft
LIBFT := $(LIBFT_DIR)/libft.a

CC := cc
CFLAGS := -g
NAME := minishell
SRCS := $(BUILT_IN_SRCS) $(ENVP_SRCS) $(UTILS_SRCS) $(TERMINAL_SRCS) \
		$(MAIN_SRCS)
OBJS := $(SRCS:.c=.o)
RM := rm
RMFLAGS := -f

.PHONY	:	all
all	:	$(NAME)

$(NAME)	:	$(OBJS) $(LIBFT) $(INCLUDE_FILES)
	$(CC) $(CFLAGS) -o $@ $(LIBFT) $(OBJS) $(LIBFT) \
		-L$(READLINE_LIB) -lreadline -lhistory

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