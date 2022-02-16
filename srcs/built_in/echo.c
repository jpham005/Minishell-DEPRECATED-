/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:50:39 by jaham             #+#    #+#             */
/*   Updated: 2022/02/16 13:57:53 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "terminal.h"

char	*make_string(const char **argv)
{
	size_t	i;
	char	*ret;
	char	*temp;

	while (argv[i])
	{

	}
}

int	echo(t_context *context, const char **argv)
{
	char	*writing;

	if (!context)
		return (1);
	if (!argv[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	writing = make_string(argv);
	if (write())
}
