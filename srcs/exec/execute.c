/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:24:03 by jaham             #+#    #+#             */
/*   Updated: 2022/02/26 12:52:29 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temphead.h"
#include "exec.h"
#include "libft.h"
#include <errno.h>
#include <stdio.h>

static int	exec_pipes(t_pipe *pipes, t_context *context)
{
	pid_t		*pids;
	t_in_out	in_out;
	size_t		i;

	pids = ft_malloc(sizeof(pid_t), pipes->len);
	init_in_out(&in_out);
	i = 0;
	while (i < pipes->len - 1)
	{
		if (!ft_pipe(in_out.curr))
			return (1);
		pids[i] = fork();
		if (pids[i] == -1)
			return (wait_all(pids, i, 1));
		if (!pids[i])
			child(&(pipes->cmds[i]), context, &in_out);
		ft_close(in_out.curr[1]);
		ft_close(in_out.prev[0]);
		in_out.prev[0] = in_out.curr[0];
		i++;
	}
	pids[i] = exec_out(&(pipes->cmds[i]), context, &in_out);
	if (pids[i] == -1)
		return (wait_all(pids, i, 1));
	return (wait_all(pids, ++i, 0));
}

static int	exec_single_cmd(t_cmd *cmd, t_context *context)
{
	int	built_in_type;
	int	*pid;

	if (!handle_redir(cmd->redir, context))
		return (1);
	built_in_type = is_built_in(cmd->cmd[0]);
	if (built_in_type != SH_NOT_BUILT_IN)
		return (exec_built_in(cmd->cmd, context, built_in_type));
	pid = ft_malloc(sizeof(int), 1);
	pid[0] = fork();
	if (pid[0] == -1)
	{
		perror("fork");
		return (1);
	}
	if (!pid[0])
	{
		if (cmd->type == SINGLE_CMD)
			exec_cmd(cmd->cmd, context);
		//else if (cmd->type == PARENTHESIS)
		//	exec_parenthesis();
	}
	return (wait_all(pid, 1, 0));
}

static int	exec_line(t_cmd_line *cmd_line, t_context *ctx)
{
	if (cmd_line->pipes->len == 1)
		return (exec_single_cmd(&(cmd_line->pipes->cmds[0]), ctx));
	else
		return (exec_pipes(cmd_line->pipes, ctx));
	return (1);
}

void	executor(t_cmd_line *cmd_line, t_context *context)
{
	while (cmd_line)
	{
		if (cmd_line->type == PIPE)
			context->exit_status = exec_line(cmd_line, context);
		else if((cmd_line->type == AND) && (context->exit_status == 0))
			context->exit_status = exec_line(cmd_line, context);
		else if ((cmd_line->type == OR) && (context->exit_status != 0))
			context->exit_status = exec_line(cmd_line, context);
		if (
			!ft_dup2(context->std_fd[0], 0)
			|| !ft_dup2(context->std_fd[1], 1)
			|| !ft_dup2(context->std_fd[2], 2)
		)
		{
			context->exit_status = 1;
			return ;
		}
		cmd_line = cmd_line->next;
	}
}
