/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_terminal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:06:57 by jaham             #+#    #+#             */
/*   Updated: 2022/02/08 21:08:14 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_TERMINAL_H
# define INIT_TERMINAL_H

# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "context.h"

# define TOO_MANY_ARG_ERR_MESSAGE "Too many arg:\n"
# define SIG_QUIT_MESSAGE "Quit: 3\n"
# define ENVP_ERR_MESSAGE "Envp init Error\n"
# define MINISHELL_WITH_COLOR RED_BD"minishell "YELLOW_BT_BD"#"DEF_COL" "RED_BT

void	set_term_default(t_context *context);
void	set_term_execute(t_context *context);
void	reset_terminal(t_context *context);
void	sig_int_handler_default(int sig);
void	sig_int_handler_exec(int sig);
void	sig_quit_handler(int sig);
int		check_arg(int argc, const char **argv);
int		check_tty(int stdin, int stdout, int stderr);
char	*ft_readline(t_context *context);

#endif