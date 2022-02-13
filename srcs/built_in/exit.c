/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:25:58 by jaham             #+#    #+#             */
/*   Updated: 2022/02/13 21:42:58 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "terminal.h"
#include "utils.h"
#include "libft.h"

static int	check_valid(const char **argv)
{
	if (!ft_isnumstr(argv[0]))
		return (EXIT_NON_NUMERIC);
	if (argv[1])
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

	if (!argv)
		exit_with_message(context->exit_status);
	state = check_valid(argv);
	if (state & EXIT_NON_NUMERIC)
	{
		printf("exit\n");
		printf(SHELL_NAME EXIT_CMD"%s: "EXIT_NON_NUMERIC_ERR_MESSAGE, argv[0]);
		exit(255);
	}
	if (state & EXIT_TOO_MANY_ARG)
	{
		printf(SHELL_NAME EXIT_CMD EXIT_TOO_MANY_ARG_ERR_MESSAGE);
		return (1);
	}
	if (state & EXIT_NUMERIC)
		exit_with_message(ft_atoi(argv[0]));
	return (0);
}

/*
exit => exit\n, term terminal with exit status
exit 4 => exit\n, term terminal with 4
exit 4 4 => bash: exit: too many arguments, doesnt exit, exit status 1
exit a => 
bash-3.2$ exit a
exit
bash: exit: a: numeric argument required
exit with 255
ignore after a, 
*/