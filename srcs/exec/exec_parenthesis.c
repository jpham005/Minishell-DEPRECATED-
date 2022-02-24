/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parenthesis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:22:54 by jaham             #+#    #+#             */
/*   Updated: 2022/02/24 20:22:53 by jaham            ###   ########.fr       */
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
	line->next = malloc(sizeof(t_cmd_line));
	line->type = PIPE;
	line->pipes = malloc(sizeof(t_pipe));
	line->pipes->len = 1;
	line->pipes->cmds = malloc(sizeof(t_cmd) * 2);
	line->pipes->cmds[0].redir = malloc(sizeof(t_redirect));
	line->pipes->cmds[0].redir->type = REDIR_IN;
	line->pipes->cmds[0].redir->target = "infile";
	line->pipes->cmds[0].redir->next = NULL;
	// line->pipes->cmds[0].redir->next = &(t_redirect) {
	// 	REDIR_OUT,
	// 	"outfile3",
	// 	NULL
	// };
	line->pipes->cmds[0].type = SINGLE_CMD;
fprintf(stderr, "parenthesis cat\n");
	line->pipes->cmds[0].cmd = ft_split("cat", ' ');
	line->pipes->cmds[1].cmd = ft_split("echo -123", ' ');
	line->pipes->cmds[1].type = SINGLE_CMD;
	line->pipes->cmds[1].redir = NULL;

	line->next->next = NULL;
	line->next->type = AND;
	line->next->pipes = malloc(sizeof(t_pipe));
	line->next->pipes->len = 1;
	line->next->pipes->cmds = &(t_cmd) {
		ft_split("echo 123", ' '),
		NULL,
		SINGLE_CMD
	};
fprintf(stderr, "start recursive %d %d %d\n", in_out->infile, in_out->outfile, fcntl(in_out->infile, F_GETFD));
	executer(line, context, in_out);
fprintf(stderr, "parenthesis exit %d\n", context->exit_status);
	exit(context->exit_status);
}
