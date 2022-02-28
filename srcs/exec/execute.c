/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:24:03 by jaham             #+#    #+#             */
/*   Updated: 2022/02/28 18:18:03 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include <stdlib.h>

int	exec_pipes(t_pipe *pipes, t_context *context, t_in_out *in_out)
{
	pid_t	*pids;
	size_t	i;
	size_t	j;
	int		ret;

	pids = ft_malloc(sizeof(pid_t), pipes->len);
	i = 0;
	j = 0;
	while (i + 1 < pipes->len)
	{
		ret = handle_redirection(pipes->cmds[i++].redir, context, in_out);
		if (!ret)
			continue ;
		if (ret == -1)
			return (1);
		pids[j] = exec_fork(&(pipes->cmds[i - 1]), context, in_out);
		if (pids[j] == -1)
			return (wait_all(pids, j, 1));
		j++;
	}
	if (handle_redirection(pipes->cmds[i].redir, context, in_out) <= 0)
		return (wait_all(pids, j, 1));
	pids[j] = exec_fork_out(&(pipes->cmds[i]), context, in_out);
	return (wait_all(pids, j + (pids[j] != -1), (pids[j] == -1)));
}

static int	care_in_out(t_cmd *cmd, t_context *context, t_in_out *in_out)
{
	if (handle_redirection(cmd->redir, context, in_out) <= 0)
		return (0);
	if (in_out->in != 0)
	{
		if (!ft_dup2(in_out->in, 0))
			exit(1);
		ft_close(in_out->in);
	}
	if (in_out->out != 1)
	{
		if (!ft_dup2(in_out->out, 1))
			exit(1);
		ft_close(in_out->out);
	}
	return (1);
}

static int	exec_single_cmd(t_cmd *cmd, t_context *context, t_in_out *in_out)
{
	int	built_in_type;
	int	*pid;

	if (!care_in_out(cmd, context, in_out))
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
	t_in_out	new;
	int			backup[2];
	int			ret;

	new.in = 0;
	new.out = 1;
	ft_close(backup[0]);
	ft_close(backup[1]);
	backup[0] = ft_dup(0);
	backup[1] = ft_dup(1);
	if (backup[0] < 0 || backup[1] < 0)
		exit(1);
	if (cmd_line->pipes->len == 1)
	{
		ret = exec_single_cmd(&(cmd_line->pipes->cmds[0]), ctx, &new);
		if (!ft_dup2(backup[0], 0) || !ft_dup2(backup[1], 1))
			exit(1);
		return (ret);
	}
	else
		return (exec_pipes(cmd_line->pipes, ctx, &new));
	return (1);
}

void	executor(t_cmd_line *cmd_line, t_context *context, t_in_out *in_out)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (in_out)
	{
		if (!ft_dup2(in_out->out, 1) || !ft_dup2(in_out->in, 0))
		{
			context->exit_status = 1;
			return ;
		}
	}
	while (cmd_line)
	{
		if (cmd_line->pipes->type == PIPE)
			context->exit_status = exec_line(cmd_line, context);
		else if ((cmd_line->pipes->type == AND) && (context->exit_status == 0))
			context->exit_status = exec_line(cmd_line, context);
		else if ((cmd_line->pipes->type == OR) && (context->exit_status != 0))
			context->exit_status = exec_line(cmd_line, context);
		cmd_line = cmd_line->next;
	}
}
