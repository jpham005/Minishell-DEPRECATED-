/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:08:08 by jaham             #+#    #+#             */
/*   Updated: 2022/02/28 20:32:26 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "terminal.h"
#include "color.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

void	sig_int_handler_readline(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	sig_int_handler_default(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", 2);
}

void	sig_quit_handler(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd(SIG_QUIT_MESSAGE, 2);
}

void	set_sig_handler_child(void)
{
	signal(SIGINT, sig_int_handler_default);
	signal(SIGQUIT, sig_quit_handler);
}
