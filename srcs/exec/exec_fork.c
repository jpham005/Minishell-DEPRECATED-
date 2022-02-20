/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:38:59 by jaham             #+#    #+#             */
/*   Updated: 2022/02/20 18:07:26 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "temphead.h"
#include "libft.h"
#include "envp.h"
#include <errno.h>

void	child(int in[2], t_out *outs, t_cmd cmd, t_envp_list *envp)
{
	if (in[0] == -1)
		exit(1);
	if (in[0] != 0 && dup2(in[0], 0) == -1)
		exit(1);
	if (in[0] != 0)
		close(in[0]);
	if (outs->out != 1)
	{
		if (dup2(outs->outpipe[1], 1) == -1)
			exit(1);
		close(outs->outpipe[1]);
		close(outs->outpipe[0]);
	}
	else
	{
		if (dup2(outs->out, 1) == -1)
			exit(1);
	}
	execve(cmd.cmd[0], cmd.cmd, convert_envp_to_dptr(envp));
	exit_by_errno(errno);
}

pid_t	exec_fork_pipe(int in[2], int *out, t_cmd cmd, t_envp_list *envp)
{
	t_out	outs;
	int		pid;

	if (*out == 1)
	{
		if (pipe(outs.outpipe) == -1)
			return (-1);
	}
	outs.out = *out;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
		child(in, &outs, cmd, envp);
	if (outs.outpipe[1] != 1)
		close(outs.outpipe[1]);
	if (in[0] != 0)
		close(in[0]);
	in[0] = outs.outpipe[0];
	return (pid);
}

pid_t	exec_fork_out(int in[2], int *out, t_cmd cmd, t_envp_list *envp)
{
	t_out	outs;
	pid_t	pid;

	if (!handle_redirection(cmd.redir, in, out))
		return (-1);
	outs.out = *out;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
		child(in, &outs, cmd, envp);
}
