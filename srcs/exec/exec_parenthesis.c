/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parenthesis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:43:17 by jaham             #+#    #+#             */
/*   Updated: 2022/03/06 19:46:01 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "parser.h"
#include <stdlib.h>

void	exec_parenthesis(char *str, t_context *context, t_in_out *in_out)
{
	t_cmd_line	*new;
	t_in_out	init_in_out;

	if (in_out)
	{
		in_out->in = ft_dup(0);
		in_out->out = ft_dup(1);
		if (in_out->in < 0 || in_out->out < 0)
			exit(1);
	}
	init_in_out.in = 0;
	init_in_out.out = 1;
	new = parse(context, str);
	if (new && in_out)
		executor(new, context, in_out);
	else if (new && !in_out)
		executor(new, context, &init_in_out);
	else
	{
		ft_putstr_fd("syntax error\n", 2);
		exit(258);
	}
	free_cmd_line(new);
	exit(context->exit_status);
}
