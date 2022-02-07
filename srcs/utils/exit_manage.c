/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:56:34 by jaham             #+#    #+#             */
/*   Updated: 2022/02/07 21:02:01 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
		return (print_exit());
	else if (status == PRT_INTRO_ERR)
		return (write_error(PRT_INTRO_ERR_MESSAGE, 1));
	else if (status == SET_TERM_ERR)
		return (write_error(SET_TERM_ERR_MESSAGE, 1));
	else if (status == EXEC_ERR)
		return (write_error(EXEC_ERR_MESSAGE, 1));
	else if (status == ARG_ERR)
		return (write_error(ARG_ERR_MESSAGE, 1));
	else if (status == DEFAULT_FD_ERR)
		return (write_error(DEFAULT_FD_ERR_MESSAGE, 1));
	else if (status == INIT_CONTEXT_ERR)
		return (write_error(INIT_CONTEXT_ERR_MESSAGE, 1));
	return (0);
}
