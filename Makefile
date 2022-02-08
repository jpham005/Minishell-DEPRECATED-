SRCS_DIR := srcs
BUILT_IN_DIR := $(SRCS_DIR)/built_in
ENVP_DIR := $(SRCS_DIR)/envp
UTILS_DIR := $(SRCS_DIR)/utils
INIT_TERMINAL_DIR := $(SRCS_DIR)/init_terminal

INCLUDE := include
INCLUDE_FILES := built_in.h color.h context.h envp.h init_terminal.h main.h \
				utils.h
INCLUDE_FILES := $(addprefix $(INCLUDE)/, $(INCLUDE_FILES))

READLINE_DIR := $(shell brew --prefix readline)
READLINE_INCLUDE := $(READLINE_DIR)/include
READLINE_LIB := $(READLINE_DIR)/lib

BUILT_IN_SRCS := export.c unset.c
BUILT_IN_SRCS := $(addprefix $(BUILT_IN_DIR)/, $(BUILT_IN_SRCS))
ENVP_SRCS := manage_envp.c envp_util.c
ENVP_SRCS := $(addprefix $(ENVP_DIR)/, $(ENVP_SRCS))
UTILS_SRCS := convert_exit_status.c exit_manage.c print_intro.c
UTILS_SRCS := $(addprefix $(UTILS_DIR)/, $(UTILS_SRCS))
INIT_TERMINAL_SRCS := check_default_term_state.c set_terminal_state.c \
						signal_handler.c context_manage.c
INIT_TERMINAL_SRCS := $(addprefix $(INIT_TERMINAL_DIR)/, $(INIT_TERMINAL_SRCS))
MAIN_SRCS := main.c
MAIN_SRCS := $(addprefix $(SRCS_DIR)/, $(MAIN_SRCS))

LIBFT_DIR := $(SRCS_DIR)/libft
LIBFT := $(LIBFT_DIR)/libft.a

CC := cc
CFALGS := -g
NAME := minishell
SRCS := $(BUILT_IN_SRCS) $(ENVP_SRCS) $(UTILS_SRCS) $(INIT_TERMINAL_SRCS) \
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