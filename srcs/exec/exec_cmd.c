/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:44:57 by jaham             #+#    #+#             */
/*   Updated: 2022/02/20 15:15:04 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "libft.h"
#include "temphead.h"
#include "exec.h"

int	wait_all(pid_t *pids, size_t i)
{
	size_t	j;
	int		status;

	j = 0;
	while (j < i - 1)
	{
		ft_waitpid(pids[j], NULL, 0);
		j++;
	}
	ft_waitpid(pids[j], &status, 0);
	if (ft_wifexited(status))
		return (ft_wexitstatus(status));
	if (ft_wifsignaled(status))
		return (ft_wtermsig(status) + 128);
	return (status % 128);
}

int	exec_single_cmd(t_pipe *pipes, int in[2], int *out, t_context *context)
{
	pid_t	*pids;
	size_t	i;

	pids = ft_malloc(sizeof(pid_t), pipes->len);
	i = 0;
	while (i < pipes->len - 1)
	{
		if (!handle_redirection(pipes->cmds[i].redir, in, out))
			return (1);
		pids[i] = exec_fork_pipe(in, out, pipes->cmds[i].cmd, context->envp);
		if (pids[i] == -1 && i > 0)
		{
			wait_all(pids, i - 1);
			return (1);
		}
		i++;
	}
	pids[i] = exec_fork_out(in, out, pipes->cmds[i].cmd, context->envp);
	return (wait_all(pids, ++i));
}

// int	exec_parenthesis

int	exec_pipes(t_pipe *pipes, t_context *context)
{
	int		in[2];
	int		out;
	pid_t	*pids;

	in[1] = 0;
	out = 1;
	if (pipes->type == SINGLE_CMD)
		return (exec_single_cmd(pipes, in, out, context));
	// else if (pipes->type == PARENTHESIS)
	// 	return (exec_parenthesis(pipes, in, out, context));
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
}
