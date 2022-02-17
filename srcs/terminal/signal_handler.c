/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:08:08 by jaham             #+#    #+#             */
/*   Updated: 2022/02/17 15:59:25 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "terminal.h"
#include <stdio.h>
#include <readline/readline.h>

void	sig_int_handler_default(int sig)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	sig_int_handler_exec(int sig)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	sig_quit_handler(int sig)
{
	ft_putstr_fd(SIG_QUIT_MESSAGE, 2);
}
