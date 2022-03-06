/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:56:34 by jaham             #+#    #+#             */
/*   Updated: 2022/03/06 13:40:48 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft.h"
#include "utils.h"
#include <stdlib.h>
#include <signal.h>

void	write_error(const char *str)
{
	ft_putstr_fd(str, 2);
}

static void	print_exit(void)
{
	ft_putstr_fd("\033[1A", 1);
	ft_putstr_fd("\033[12C", 1);
	ft_putstr_fd("exit\n", 1);
}

int	exit_with_status(int status)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (status & END_TERM)
	{
		print_exit();
		write(1, DEF_COL, 6);
		return (0);
	}
	if (status & ARG_ERR)
		write_error(ARG_ERR_MESSAGE);
	else if (status & DEFAULT_FD_ERR)
		write_error(DEFAULT_FD_ERR_MESSAGE);
	else if (status & PRINT_INTRO_ERR)
		write_error(PRT_INTRO_ERR_MESSAGE);
	write(1, DEF_COL, 6);
	exit(1);
}
