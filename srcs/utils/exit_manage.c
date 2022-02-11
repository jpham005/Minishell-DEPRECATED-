/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:56:34 by jaham             #+#    #+#             */
/*   Updated: 2022/02/11 18:52:47 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "color.h"

int	print_error(const char *str, int ret)
{
	perror(str);
	return (ret);
}

int	write_error(const char *str, int ret)
{
	ft_putstr_fd(str, 2);
	return (ret);
}

static int	print_exit(void)
{
	ft_putstr_fd("\033[1A", 1);
	ft_putstr_fd("\033[12C", 1);
	ft_putstr_fd("exit\n", 1);
	return (SUCCESS);
}

int	exit_with_status(int status)
{
	if (status == END_TERM)
	{
		print_exit();
		write(1, DEF_COL, 6);
		return (0);
	}
	if (status == ARG_ERR)
		write_error(ARG_ERR_MESSAGE, 1);
	else if (status == DEFAULT_FD_ERR)
		write_error(DEFAULT_FD_ERR_MESSAGE, 1);
	else if (status == INIT_CONTEXT_ERR)
		write_error(INIT_CONTEXT_ERR_MESSAGE, 1);
	else if (status == PRT_INTRO_ERR)
		write_error(PRT_INTRO_ERR_MESSAGE, 1);
	write(1, DEF_COL, 6);
	exit(1);
}
