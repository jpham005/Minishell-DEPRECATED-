/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:44:57 by jaham             #+#    #+#             */
/*   Updated: 2022/02/18 20:39:55 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "terminal.h"
#include "libft.h"
#include "temphead.h"

int	executer(t_command *parse, t_context *context)
{
	int	built_in;

	while (parse)
	{
		if (parse->type == PIPE)
			context->exit_status = exec_pipeline(parse->cmd_struct);
		else if (parse->type == AND)
		{
			context->exit_status
		}
		else if (parse->type == OR)
		{

		}
	}
}
