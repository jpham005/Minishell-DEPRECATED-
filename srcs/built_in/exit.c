/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:25:58 by jaham             #+#    #+#             */
/*   Updated: 2022/02/12 19:58:17 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "terminal.h"

static int	check_valid(const char **argv)
{
	
}

int	built_in_exit(t_context *context, const char **argv)
{
	if (!argv)
		exit(context->exit_status);
	check_valid(argv);
}

/*
exit => exit\n, term terminal with exit status
exit 4 => exit\n, term terminal with 4
exit 4 4 => bash: exit: too many arguments, doesnt exit, exit status 1
exit a => 
bash-3.2$ exit a
exit
bash: exit: a: numeric argument required
ignore after a, 
if numeric after non numeric,
exit a 4
exit: too many arguments , exit with 1
*/