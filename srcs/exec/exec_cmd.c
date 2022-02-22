/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:44:57 by jaham             #+#    #+#             */
/*   Updated: 2022/02/22 21:11:41 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "libft.h"
#include "temphead.h"
#include "exec.h"
#include <stdlib.h>

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

// int	exec_parenthesis

static int	exec_pipes(t_pipe *pipes, t_context *context, t_in_out *in_out)
{
	t_in_out	new;

	if (!in_out)
	{
		new.infile = context->std_fd[0];
		new.outfile = context->std_fd[1];
		return (exec_cmd(&new, pipes, context));
	}
	return (exec_cmd(in_out, pipes, context));
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
		dup2(context->std_fd[0], 0);
		dup2(context->std_fd[1], 1);
		dup2(context->std_fd[2], 2);
	}
	return (1);
}
