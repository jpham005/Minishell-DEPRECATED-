/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:44:57 by jaham             #+#    #+#             */
/*   Updated: 2022/02/19 21:27:52 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "libft.h"
#include "temphead.h"
#include "exec.h"

int	handle_redirection(t_redirect *redir, int in[2], int *out)
{
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			if (!handle_inpipe(in, redir, redir->type, redir->target))
				return (0);
		else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			if (!handle_out(out, redir))
				return (0);
		redir = redir->next;
	}
	return (1);
}


int	exec_pipes(t_pipe *pipes, t_context *context)
{
	size_t	i;
	int		in[2];
	int		out;
	pid_t	*pids;

	i = 0;
	in[1] = 0;
	out = 1;
	pids = ft_malloc(sizeof(pid_t), pipes->len);
	while (i < pipes->len)
	{
		if (!handle_redirection(pipes->cmds[i].redir, in, &out))
			return (1);
		pids[i] = exec_fork(in, out, pipes->cmds[i].cmd, context->envp);
		// execve
		i++;
	}
}

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
