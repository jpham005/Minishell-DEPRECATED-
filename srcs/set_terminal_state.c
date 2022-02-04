/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:20:16 by jaham             #+#    #+#             */
/*   Updated: 2022/02/04 11:10:22 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set_terminal_state.h"
#include "exit_manage.h"
#include "libft.h"

void	sig_int_handler_default(int sig)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

static void	sig_int_handler_exec(int sig)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
}

static void	sig_quit_handler(int sig)
{
	ft_putstr_fd(SIG_QUIT_MESSAGE, 2);
}

int	set_term_default(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) < 0)
		return (print_error(NULL, 0));
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
		return (print_error(NULL, 0));
	signal(SIGINT, sig_int_handler_default);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

int	set_term_execute(void)
{
	struct termios	term;

	signal(SIGQUIT, sig_quit_handler);
	signal(SIGINT, sig_int_handler_exec);
	return (1);
}
