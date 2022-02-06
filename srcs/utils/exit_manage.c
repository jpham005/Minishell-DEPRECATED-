/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:56:34 by jaham             #+#    #+#             */
/*   Updated: 2022/02/05 20:49:13 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	print_error(const char *str, int ret)
{
	perror(str);
	return (ret);
}

static int	write_error(const char *str)
{
	ft_putstr_fd(str, 2);
	return (FAIL);
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
		return (write_error(PRT_INTRO_ERR_MESSAGE));
	else if (status == SET_TERM_ERR)
		return (write_error(SET_TERM_ERR_MESSAGE));
	else if (status == EXEC_ERR)
		return (write_error(EXEC_ERR_MESSAGE));
	else if (status == ARG_ERR)
		return (write_error(ARG_ERR_MESSAGE));
	else if (status == ENVP_ERR)
		return (write_error(ENVP_ERR_MESSAGE));
	return (0);
}
