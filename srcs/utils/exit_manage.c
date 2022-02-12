/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:56:34 by jaham             #+#    #+#             */
/*   Updated: 2022/02/12 18:00:12 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "color.h"

int	write_error(const char *str, int ret)
{
	ft_putstr_fd(str, 2);
	return (ret);
}

static void	print_exit(void)
{
	ft_putstr_fd("\033[1A", 1);
	ft_putstr_fd("\033[12C", 1);
	ft_putstr_fd("exit\n", 1);
}

int	exit_with_status(int status)
{
	if (status & END_TERM)
	{
		print_exit();
		write(1, DEF_COL, 6);
		return (0);
	}
	if (status & ARG_ERR)
		write_error(ARG_ERR_MESSAGE, 1);
	else if (status & DEFAULT_FD_ERR)
		write_error(DEFAULT_FD_ERR_MESSAGE, 1);
	else if (status & PRINT_INTRO_ERR)
		write_error(PRT_INTRO_ERR_MESSAGE, 1);
	write(1, DEF_COL, 6);
	exit(1);
}
