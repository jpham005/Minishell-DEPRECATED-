# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaham <jaham@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 20:45:33 by jaham             #+#    #+#              #
#    Updated: 2022/03/12 20:06:15 by jaham            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR := srcs
BUILT_IN_DIR := $(SRCS_DIR)/built_in
ENVP_DIR := $(SRCS_DIR)/envp
UTILS_DIR := $(SRCS_DIR)/utils
TERMINAL_DIR := $(SRCS_DIR)/terminal
EXEC_DIR := $(SRCS_DIR)/exec
PARSER_DIR := $(SRCS_DIR)/parser

INCLUDE := include
INCLUDE_FILES := built_in.h color.h envp.h terminal.h utils.h exec.h parser.h \
				cmd_line.h intro_img.h
INCLUDE_FILES := $(addprefix $(INCLUDE)/, $(INCLUDE_FILES))

READLINE_DIR := $(shell brew --prefix readline)
READLINE_INCLUDE := $(READLINE_DIR)/include
READLINE_LIB := $(READLINE_DIR)/lib

BUILT_IN_SRCS := export.c unset.c env.c pwd.c exit.c cd.c cd_util.c echo.c
BUILT_IN_SRCS := $(addprefix $(BUILT_IN_DIR)/, $(BUILT_IN_SRCS))
ENVP_SRCS := init_destroy.c util.c print.c tool.c
ENVP_SRCS := $(addprefix $(ENVP_DIR)/, $(ENVP_SRCS))
UTILS_SRCS := exit_manage.c print_intro.c clear_cmd_line.c
UTILS_SRCS := $(addprefix $(UTILS_DIR)/, $(UTILS_SRCS))
PARSER_SRCS := expand_asterisks.c par2.c util_struct.c tokenizer.c \
		expand_dollars.c token_to_cmd_line.c free.c parse.c \
		expand_asterisks_helper.c precheck_syntax_err.c \
		expand_dollars_helper.c expand_dollars_helper2.c \
		expand_asterisks2.c expand_dollars_helper3.c token_to_cmd_line2.c \
		token_to_cmd_line3.c token_to_cmd_line4.c tokenizer2.c tokenizer3.c \
		token_to_cmd_line5.c token_to_cmd_line_quote.c \
		token_to_cmd_line_helper.c
PARSER_SRCS := $(addprefix $(PARSER_DIR)/, $(PARSER_SRCS))
TERMINAL_SRCS := check_default_state.c set_state.c signal_handler.c init.c \
				readline_loop.c check_valid_str.c signal_handler_exec.c
TERMINAL_SRCS := $(addprefix $(TERMINAL_DIR)/, $(TERMINAL_SRCS))
EXEC_SRCS := exec_built_in.c execute.c redirection.c exec_cmd.c wait_all.c \
			exec_child.c exec_parenthesis.c redirection_util.c \
			redirection_heredoc.c free_err_info.c split_string_with_sep.c
EXEC_SRCS := $(addprefix $(EXEC_DIR)/, $(EXEC_SRCS))
MAIN_SRCS := main.c
MAIN_SRCS := $(addprefix $(SRCS_DIR)/, $(MAIN_SRCS))

LIBFT_DIR := $(SRCS_DIR)/libft
LIBFT := $(LIBFT_DIR)/libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror
NAME := minishell
SRCS := $(BUILT_IN_SRCS) $(ENVP_SRCS) $(UTILS_SRCS) $(TERMINAL_SRCS) \
		$(PARSER_SRCS) $(EXEC_SRCS) $(MAIN_SRCS)
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
