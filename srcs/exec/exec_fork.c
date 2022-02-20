/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:38:59 by jaham             #+#    #+#             */
/*   Updated: 2022/02/20 15:04:40 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "temphead.h"
#include "libft.h"
#include "envp.h"
#include <errno.h>

void	child(int in[2], int outpipe[2], t_cmd cmd, t_envp_list *envp)
{
	if (in[0] == -1)
		exit(1);
	if (dup2(in[0], 0) == -1)
		exit(1);
	close(in[0]);
	if (outpipe[1] != 1)
	{
		if (dup2(outpipe[1], 1) == -1)
			exit(1);
		close(outpipe[1]);
		close(outpipe[0]);
	}
	execve(cmd.cmd[0], cmd.cmd, convert_envp_to_dptr(envp));
	exit_by_errno(errno);
}

pid_t	exec_fork_pipe(int in[2], int *out, t_cmd cmd, t_envp_list *envp)
{
	int		outpipe[2];
	int		pid;

	outpipe[1] = 1;
	if (*out != 1)
	{
		if (pipe(outpipe) == -1)
			return (-1);
	}
	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
		child(in, outpipe, cmd, envp);
	if (outpipe[1] != 1)
		close(outpipe[1]);
	close(in[0]);
	in[0] = outpipe[0];
	return (pid);
}
