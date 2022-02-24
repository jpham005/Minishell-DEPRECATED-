/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:44:57 by jaham             #+#    #+#             */
/*   Updated: 2022/02/24 21:47:53 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "libft.h"
#include "temphead.h"
#include "exec.h"
#include <stdlib.h>
#include <errno.h>

int	exec_cmd(t_in_out *in_out, t_pipe *pipes, t_context *context)
{
	pid_t	*pids;
	size_t	i;
	size_t	j;

	pids = ft_malloc(sizeof(pid_t), pipes->len);
	i = 0;
	j = 0;
	while (pipes->len-- > 1)
	{
		in_out->outfile = 1;
		if (!handle_redirection(pipes->cmds[j].redir, in_out, context))
		{
			j++;
			continue ;
		}
		pids[i] = exec_fork_pipe(pipes->cmds[j], context, in_out);
		if (pids[i] == -1)
			return (wait_all(pids, i, 1));
		i++;
		j++;
	}
	pids[i] = exec_fork_out(pipes->cmds[j], context, in_out);
	if (pids[i] == -1)
		return (wait_all(pids, i, 1));
	return (wait_all(pids, ++i, 0));
}

static void	child_single_cmd(t_cmd cmd, t_context *context, t_in_out *in_out)
{
	if (!ft_dup2(in_out->infile, 0))
		exit(1);
	ft_close(in_out->infile);
	if (!ft_dup2(in_out->outfile, 1))
		exit(1);
	ft_close(in_out->outfile);
	check_cmd_type(&cmd, context, in_out, NULL);
	execve(cmd.cmd[0], cmd.cmd, convert_envp_to_dptr(context->envp));
	exit_by_errno(errno, cmd.cmd[0]);
}

static int	exec_cmd_one(t_in_out *in_out, t_pipe *pipes, t_context *context)
{
	int	ret;
	int	pid;

	if (pipes->cmds[0].type == PARENTHESIS)
		return (exec_parenthesis(pipes->cmds, context, in_out));
	if (!handle_redirection(pipes->cmds[0].redir, in_out, context))
		return (1);
	if (!ft_dup2(in_out->outfile, 1))
		return (1);
	ret = exec_built_in(pipes->cmds[0], context, RETURN);
	if (!ft_dup2(context->std_fd[1], 1))
		return (1);
	if (ret != NOT_BUILT_IN)
		return (ret);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
		child_single_cmd(pipes->cmds[0], context, in_out);
	waitpid(pid, &ret, 0);
	if (ft_wifexited(ret))
		return (ft_wexitstatus(ret));
	if (ft_wifsignaled(ret))
		return (ft_wtermsig(ret) + 128);
	return (ret % 128);
}
#include <stdio.h>
static int	exec_pipes(t_pipe *pipes, t_context *context, t_in_out *in_out)
{
	t_in_out	new;

	new.infile = 0;
	new.outfile = 1;
	if (in_out)
	{
		new.infile = in_out->infile;
		new.outfile = in_out->outfile;
		fprintf(stderr, "%d %d\n", new.infile, new.outfile);
	}
	if (pipes->len == 1)
		return (exec_cmd_one(&new, pipes, context));
	return (exec_cmd(&new, pipes, context));
}

// called first when starting executor, returns 1 or 0 to indicate error
// arg : cmd_line, context(envp)
int	executer(t_cmd_line *cmd_line, t_context *context, t_in_out *in_out)
{
	while (cmd_line)
	{
		if (cmd_line->type == PIPE)
			context->exit_status = exec_pipes(cmd_line->pipes, context, in_out);
		else if ((cmd_line->type == AND) && !context->exit_status)
			context->exit_status = exec_pipes(cmd_line->pipes, context, in_out);
		else if ((cmd_line->type == OR) && context->exit_status)
			context->exit_status = exec_pipes(cmd_line->pipes, context, in_out);
		cmd_line = cmd_line->next;
		// dup2(context->std_fd[0], 0);
		// dup2(context->std_fd[1], 1);
		// dup2(context->std_fd[2], 2);
	}
	return (1);
}
