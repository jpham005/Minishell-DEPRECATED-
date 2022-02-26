/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:24:03 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 08:08:02 by jaham            ###   ########.fr       */
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
			exec_parenthesis(cmd->cmd[0], context);
		if (cmd->type == SINGLE_CMD)
			exec_cmd(cmd->cmd, context);
	}
	return (pid);
}

int	replace_stdio(t_in_out *in_out, t_context *context)
{
	if (in_out->prev[0] == -1)
		dup2(context->std_fd[0], STDIN_FILENO);
	else
		ft_dup2(in_out->prev[0], STDIN_FILENO);
	if (in_out->curr[0] == -1)
		dup2(context->std_fd[1], STDOUT_FILENO);
	else
		ft_dup2(in_out->curr[1], STDOUT_FILENO);
	return (1);
}

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
		if (i == 0)
			handle_pipe(&in_out, IS_PIPE_END, context);
		else if (!handle_pipe(&in_out, IS_PIPE_CONTINUE, context))
			return (1);
		replace_stdio(&in_out, context);
		if (!handle_redir(pipes->cmds[i].redir, context))
			return (1);
		pids[i] = fork_exec(&(pipes->cmds[i]), context, &in_out);
		i++;
	}
	if (!handle_pipe(&in_out, IS_PIPE_CONTINUE, context))
		return (1);
	replace_stdio(&in_out, context);
	handle_redir(pipes->cmds[i].redir, context);
	pids[i] = fork_exec(&(pipes->cmds[i]), context, &in_out);
	close_pipes(in_out.prev);
	return (wait_all(pids, i + (pids[i] != -1), 0));
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
			exec_parenthesis(cmd->cmd[0], context);
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
