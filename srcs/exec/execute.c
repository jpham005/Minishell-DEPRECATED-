/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:24:03 by jaham             #+#    #+#             */
/*   Updated: 2022/02/25 17:36:30 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temphead.h"
#include "exec.h"
#include "term.h"
#include <stdio.h>

static int	exec_single_cmd(t_cmd *cmd, t_context *context)
{
	int	built_in_type;
	int	pid;

	if (!handle_redir(cmd->redir, context))
		return (1);
	built_in_type = is_built_in(cmd->cmd[0]);
	if (built_in_type != SH_NOT_BUILT_IN)
		return (exec_built_in(cmd->cmd, context, built_in_type));
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (!pid)
	{
		if (cmd->type == SINGLE_CMD)
			exec_cmd(cmd->cmd, context);
		//else if (cmd->type == PARENTHESIS)
		//	exec_parenthesis();
	}
	return (wait_all(pid));
}

static int	exec_line(t_cmd_line *cmd_line, t_context *ctx, t_in_out *in_out)
{
	if (cmd_line->pipes->len == 1)
		return (exec_single_cmd(&(cmd_line->pipes->cmds[0]), ctx));
	//else
	//	exec_pipes(cmd_line->pipes, ctx);
	return (1);
}

void	executor(t_cmd_line *cmd_line, t_context *context, t_in_out *in_out)
{
	while (cmd_line)
	{
		if (cmd_line->type == PIPE)
			context->exit_status = exec_line(cmd_line, context, in_out);
		else if((cmd_line->type == AND) && (context->exit_status == 0))
			context->exit_status = exec_line(cmd_line, context, in_out);
		else if ((cmd_line->type == OR) && (context->exit_status != 0))
			context->exit_status = exec_line(cmd_line, context, in_out);
		cmd_line = cmd_line->next;
	}
}
