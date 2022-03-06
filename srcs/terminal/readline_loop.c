/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:54:45 by jaham             #+#    #+#             */
/*   Updated: 2022/03/06 15:34:48 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "exec.h"
#include "libft.h"
#include "parser.h"
#include "terminal.h"
#include "utils.h"
#include <stdlib.h>

void	readline_loop(t_context *context)
{
	char		*str;
	t_cmd_line	*cmd_line;

	while (1)
	{
		str = ft_readline(context, NULL);
		if (!str)
			exit(exit_with_status(END_TERM));
		if (!check_valid_str(str, context))
		{
			safe_free((void **) &str);
			continue ;
		}
		cmd_line = parse(context, str);
		safe_free((void **) &str);
		if (!cmd_line)
		{
			ft_putstr_fd("syntax error\n", 2);
			context->exit_status = 258;
			continue ;
		}
		executor(cmd_line, context, NULL);
		free_cmd_line(cmd_line);
	}
}