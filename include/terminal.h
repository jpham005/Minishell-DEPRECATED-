/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:06:57 by jaham             #+#    #+#             */
/*   Updated: 2022/02/12 18:01:28 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "envp.h"

# define TOO_MANY_ARG_ERR_MESSAGE "Too many arg: "
# define SIG_QUIT_MESSAGE "Quit: 3\n"
# define MINISHELL_WITH_COLOR RED_BD"minishell "YELLOW_BT_BD"#"DEF_COL" "RED_BT

typedef struct termios	t_term;

typedef struct s_context
{
	int				std_fd[3];
	unsigned int	exit_status;
	t_envp_list		*envp;
}	t_context;

typedef struct s_term_state
{
	t_term	default_term;
	t_term	rl_term;
}	t_term_state;

void	set_term_default(t_term_state *term_state);
void	set_term_execute(t_term_state *term_state);
void	reset_terminal(t_context *context);
void	sig_int_handler_default(int sig);
void	sig_int_handler_exec(int sig);
void	sig_quit_handler(int sig);
int		check_arg(int argc, const char **argv);
int		check_tty(int stdin, int stdout, int stderr);
void	init_shell(t_context *context, t_term_state *state, const char **envp);
char	*ft_readline(t_term_state *term_state);

#endif