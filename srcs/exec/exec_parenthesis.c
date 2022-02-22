/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parenthesis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:22:54 by jaham             #+#    #+#             */
/*   Updated: 2022/02/22 20:32:48 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "terminal.h"
#include "temphead.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
void	exec_parenthesis(t_cmd *cmd, t_context *context, t_in_out *in_out)
{
	t_cmd_line	*line = malloc(sizeof(t_cmd_line));
	line->next = NULL;
	line->type = PIPE;
	line->pipes = malloc(sizeof(t_pipe));
	line->pipes->len = 1;
	line->pipes->cmds = malloc(sizeof(t_cmd));
	line->pipes->cmds->redir = NULL;
	line->pipes->cmds->type = SINGLE_CMD;
fprintf(stderr, "tet\n");
	line->pipes->cmds->cmd = ft_split("ls", ' ');
	executer(line, context, in_out);
fprintf(stderr, "%d\n", context->exit_status);
	exit(context->exit_status);
}
