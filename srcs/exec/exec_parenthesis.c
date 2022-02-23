/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parenthesis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:22:54 by jaham             #+#    #+#             */
/*   Updated: 2022/02/23 21:09:40 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "terminal.h"
#include "temphead.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
void	exec_parenthesis(t_cmd *cmd, t_context *context, t_in_out *in_out)
{
	// dup2(0, 0);
	// dup2(1, 1);
	// char *args[] = {
	// 	"/bin/cat",
	// 	NULL
	// };
	// execve("/bin/cat", args, NULL);
	t_cmd_line	*line = malloc(sizeof(t_cmd_line));
	line->next = NULL;
	line->type = PIPE;
	line->pipes = malloc(sizeof(t_pipe));
	line->pipes->len = 2;
	line->pipes->cmds = malloc(sizeof(t_cmd) * 2);
	line->pipes->cmds[0].redir = NULL;
	line->pipes->cmds[0].type = SINGLE_CMD;
fprintf(stderr, "parenthesis cat\n");
	line->pipes->cmds[0].cmd = ft_split("cat", ' ');
	line->pipes->cmds[1].cmd = ft_split("cat -e", ' ');
	line->pipes->cmds[1].type = SINGLE_CMD;
	line->pipes->cmds[1].redir = NULL;
fprintf(stderr, "start recursive %d %d %d\n", in_out->infile, in_out->outfile, fcntl(in_out->infile, F_GETFD));
	executer(line, context, in_out);
fprintf(stderr, "parenthesis exit %d\n", context->exit_status);
	exit(context->exit_status);
}
