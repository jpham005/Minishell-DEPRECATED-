/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:38:59 by jaham             #+#    #+#             */
/*   Updated: 2022/02/21 20:37:05 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "temphead.h"
#include "libft.h"
#include "envp.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h> // test
#include <fcntl.h>
void	child(t_cmd cmd, t_context *context, t_in_out *in_out, int outpipe[2])
{
	if (in_out->infile == -1)
		exit(1);
	if (!ft_dup2(in_out->infile, 0))
		exit(1);
	close(in_out->infile);
	if (in_out->outfile == 1)
	{
		if (!ft_dup2(outpipe[1], 1))
			exit(1);
		close(outpipe[1]);
		close(outpipe[0]);
	}
	else
	{
		if (!ft_dup2(in_out->outfile, 1))
			exit(1);
		close(in_out->outfile);
	}
	execve(cmd.cmd[0], cmd.cmd, convert_envp_to_dptr(context->envp)); // concat with path
	exit_by_errno(errno, cmd.cmd[0]);
}

pid_t	exec_fork_pipe(t_cmd cmd, t_context *context, t_in_out *in_out)
{
	pid_t	pid;
	int		outpipe[2];

	if (in_out->outfile == 1)
	{
		if (!ft_pipe(outpipe))
			return (-1);
	}
	pid = fork();
	if (pid == -1)
		return (pid);
	if (!pid)
		child(cmd, context, in_out, outpipe);
	close(outpipe[1]);
	close(in_out->infile);
	if (in_out->outfile == 1)
	{
		in_out->infile = outpipe[0];
		//printf("%d\n", in_out->infile);
		// printf("byme %s", get_next_line(in_out->infile));
	}
	else
		in_out->infile = 0;
	return (pid);
}

pid_t	exec_fork_out(t_cmd cmd, t_context *context, t_in_out *in_out)
{
	pid_t	pid;

	in_out->outfile = 1;
	if (!handle_redirection(cmd.redir, in_out, context))
		return (-1);
	pid = fork();
	if (pid == -1)
		return (pid);
	if (!pid)
	{
		if (!ft_dup2(in_out->infile, 0))
			exit(1);
		close(in_out->infile);
		if (!ft_dup2(in_out->outfile, 1))
			exit(1);
		if (in_out->outfile != 1)
			close(in_out->outfile);
		execve(cmd.cmd[0], cmd.cmd, convert_envp_to_dptr(context->envp));
		exit_by_errno(errno, cmd.cmd[0]);
	}
	close(in_out->infile);
	close(in_out->outfile);
	return (pid);
}
