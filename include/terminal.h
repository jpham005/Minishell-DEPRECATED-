/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:06:57 by jaham             #+#    #+#             */
/*   Updated: 2022/03/07 11:54:40 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include "color.h"
# include "envp.h"
# include <termios.h>

# define TOO_MANY_ARG_ERR_MESSAGE "Too many arg: "
# define SIG_QUIT_MESSAGE "Quit: 3\n"
# define MINISHELL_WITH_COLOR RED_BD"minishell "YELLOW_BT_BD"#"DEF_COL" "RED_BT
# define SYNTAX_ERR_MESSAGE "syntax error\n"

typedef struct termios	t_term;

typedef struct s_term_state
{
	t_term	default_term;
	t_term	rl_term;
}	t_term_state;

typedef struct s_context
{
	int				std_fd[3];
	int				exit_status;
	int				parse_result;
	t_envp_list		*envp;
	t_term_state	term_state;
}	t_context;

void	reset_terminal(t_context *context);
void	sig_int_handler_readline(int sig);
void	sig_int_handler_default(int sig);
void	set_sig_handler_child(void);
void	set_sig_handler_parent(char **cmd);
void	heredoc_handler(int sig);
void	sig_quit_handler(int sig);
int		check_arg(int argc, const char **argv);
int		check_tty(int stdin, int stdout, int stderr);
void	init_shell(t_context *context, const char **envp);
char	*ft_readline(t_context *context, char *str);
void	readline_loop(t_context *context);
int		check_valid_str(const char *str, t_context *context);
void	handle_syntax_err(t_context *context);

#endif