/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:24:03 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 09:32:06 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temphead.h"
#include "exec.h"
#include "libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static pid_t	fork_exec(t_cmd *cmd, t_context *context, t_in_out *in_out)
{
	pid_t			pid;
	t_sh_built_in	built_in_type;

	pid = ft_fork();
	if (!pid)
	{
		close_pipes(in_out->prev);
		close_pipes(in_out->curr);
		built_in_type = is_built_in(cmd->cmd[0]);
		if (built_in_type != SH_NOT_BUILT_IN)
			exit(exec_built_in(cmd->cmd, context, built_in_type));
		if (cmd->type == PARENTHESIS)
			exec_parenthesis(cmd->cmd[0], context, in_out);
		if (cmd->type == SINGLE_CMD)
			exec_cmd(cmd->cmd, context);
	}
	return (pid);
}

int	exec_pipes(t_pipe *pipes, t_context *context)
{
	t_in_out	in_out;
	pid_t		*pids;
	size_t		i;

	pids = ft_malloc(sizeof(pid_t), pipes->len);
	init_in_out(&in_out);
	handle_pipe(&in_out, NO_PIPE, context);
	replace_stdio(&in_out, context);
	if (handle_redir(pipes->cmds[0].redir, context))
		pids[0] = fork_exec(&(pipes->cmds[0]), context, &in_out);
	i = 1;
	while (i < pipes->len)
	{
		handle_pipe(&in_out, i + 1 == pipes->len, context);
		replace_stdio(&in_out, context);
		if (handle_redir(pipes->cmds[0].redir, context))
			pids[i] = fork_exec(&(pipes->cmds[i]), context, &in_out);
		i++;
	}
	ft_close(in_out.prev[0]);
	ft_close(in_out.prev[1]);
	return (wait_all(pids, i, 0));
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
	pid[0] = ft_fork();
	if (!pid[0])
	{
		if (cmd->type == SINGLE_CMD)
			exec_cmd(cmd->cmd, context);
		else
			exec_parenthesis(cmd->cmd[0], context, NULL);
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
		else if ((cmd_line->type == AND) && (context->exit_status == 0))
			context->exit_status = exec_line(cmd_line, context);
		else if ((cmd_line->type == OR) && (context->exit_status != 0))
			context->exit_status = exec_line(cmd_line, context);
		cmd_line = cmd_line->next;
		if (
			!ft_dup2(context->curr_fd[0], 0)
			|| !ft_dup2(context->curr_fd[1], 1)
			|| !ft_dup2(context->curr_fd[2], 2)
		)
		{
			context->exit_status = 1;
			return ;
		}
	}
}
