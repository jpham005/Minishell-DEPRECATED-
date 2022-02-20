/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:44:57 by jaham             #+#    #+#             */
/*   Updated: 2022/02/20 20:19:37 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "libft.h"
#include "temphead.h"
#include "exec.h"
#include <stdlib.h>
#include <stdio.h> // test
int	wait_all(pid_t *pids, size_t i, int ret)
{
	size_t	j;
	int		status;

	j = 0;
	while (i-- > 1)
	{
		if (pids[j] != -1)
			ft_waitpid(pids[j], NULL, 0);
		j++;
	}
	if (pids[j] != -1)
		ft_waitpid(pids[j], &status, 0);
	free(pids);
	if (ret)
		return (ret);
	if (ft_wifexited(status))
	{
		// printf(" exited %d\n", status);
		return (ft_wexitstatus(status));
	}
	if (ft_wifsignaled(status))
	{
		// printf("signaled %d\n", status);
		return (ft_wtermsig(status) + 128);
	}
	return (status % 128);
}

int	exec_single_cmd(t_pipe *pipes, int in[2], int *out, t_context *context)
{
	pid_t	*pids;
	size_t	i;

	pids = ft_malloc(sizeof(pid_t), pipes->len);
	i = 0;
	while (pipes->len-- > 1)
	{
		if (!handle_redirection(pipes->cmds[i].redir, in, out))
			continue ;
		pids[i] = exec_fork_pipe(in, out, pipes->cmds[i], context->envp);
		if (pids[i] == -1)
		{
			wait_all(pids, i, 1);
			return (1);
		}
		i++;
	}
	pids[i] = exec_fork_out(in, out, pipes->cmds[i], context->envp);
	if (pids[i] == -1)
	{
		wait_all(pids, i, 1);
		return (1);
	}
	return (wait_all(pids, ++i, 0));
}

// int	exec_parenthesis

int	exec_pipes(t_pipe *pipes, t_context *context)
{
	int		in[2];
	int		out;
	pid_t	*pids;

	in[0] = 0;
	in[1] = 0;
	out = 1;
	if (pipes->type == SINGLE_CMD)
		return (exec_single_cmd(pipes, in, &out, context));
	// else if (pipes->type == PARENTHESIS)
	// 	return (exec_parenthesis(pipes, in, out, context));
	return (5);
}

// called first when starting executor, returns 1 or 0 to indicate error
// arg : cmd_line, context(envp)
int	executer(t_cmd_line *cmd_line, t_context *context)
{
	while (cmd_line)
	{
		if (cmd_line->type == PIPE)
			context->exit_status = exec_pipes(cmd_line->pipes, context);
		else if ((cmd_line->type == AND) && !context->exit_status)
			context->exit_status = exec_pipes(cmd_line->pipes, context);
		else if ((cmd_line->type == OR) && context->exit_status)
			context->exit_status = exec_pipes(cmd_line->pipes, context);
		cmd_line = cmd_line->next;
	}
	return (1);
}
