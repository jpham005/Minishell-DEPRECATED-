/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:25:58 by jaham             #+#    #+#             */
/*   Updated: 2022/02/19 20:07:59 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	check_valid(const char **argv)
{
	if (!argv[1])
		return (EXIT_NO_ARG);
	if (!ft_isnumstr(argv[1]))
		return (EXIT_NON_NUMERIC);
	if (argv[2])
		return (EXIT_TOO_MANY_ARG);
	return (EXIT_NUMERIC);
}

static void	exit_with_message(int status)
{
	printf("exit\n");
	exit(status);
}

int	built_in_exit(t_context *context, const char **argv)
{
	int	state;

	state = check_valid(argv);
	if (state & EXIT_NO_ARG)
		exit_with_message(context->exit_status);
	if (state & EXIT_NON_NUMERIC)
	{
		printf("exit\n");
		printf(SHELL_NAME EXIT_CMD"%s: "EXIT_NON_NUMERIC_ERR_MESSAGE, argv[1]);
		exit(255);
	}
	if (state & EXIT_TOO_MANY_ARG)
	{
		printf("exit\n");
		printf(SHELL_NAME EXIT_CMD EXIT_TOO_MANY_ARG_ERR_MESSAGE);
		return (1);
	}
	if (state & EXIT_NUMERIC)
		exit_with_message(ft_atoi(argv[1]));
	return (0);
}
