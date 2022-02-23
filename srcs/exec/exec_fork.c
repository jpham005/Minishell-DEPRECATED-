/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:38:59 by jaham             #+#    #+#             */
/*   Updated: 2022/02/23 21:37:43 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "temphead.h"
#include "libft.h"
#include "envp.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
void	try_cmd(t_cmd *cmd, t_context *context)
{
	char		**path;
	char		*temp;
	char		*new;
	size_t		i;
	struct stat	status;

	exec_built_in(cmd, context);
	path = ft_split(find_list_by_key(context->envp, "PATH")->value, ':');
	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		new = ft_strjoin(temp, cmd->cmd[0]);
		if (lstat(new, &status) != -1)
			break ;
		safe_free((void **) &temp);
		safe_free((void **) &new);
		i++;
	}
	if (new)
	{
		free(cmd->cmd[0]);
		cmd->cmd[0] = new;
	}
}

void	check_cmd_type(t_cmd *cmd, t_context *context, \
											t_in_out *in_out, int *outpipe)
{
	if (cmd->type == SINGLE_CMD)
	{
		if (outpipe)
			close(outpipe[0]);
		try_cmd(cmd, context);
	}
	else if (cmd->type == PARENTHESIS)
	{
		in_out->infile = outpipe[0];
		exec_parenthesis(cmd, context, in_out);
	}
}

void	child(t_cmd cmd, t_context *context, t_in_out *in_out, int outpipe[2])
{
	if (in_out->infile && !ft_dup2(in_out->infile, 0))
		exit(1);
	if (in_out->infile)
		close(in_out->infile);
	if (in_out->outfile == 1)
	{
		if (!ft_dup2(outpipe[1], 1))
			exit(1);
	}
	else
	{
		if (!ft_dup2(in_out->outfile, 1))
			exit(1);
		close(in_out->outfile);
	}
	// close(outpipe[0]);
	close(outpipe[1]);
	check_cmd_type(&cmd, context, in_out, outpipe);
	execve(cmd.cmd[0], cmd.cmd, convert_envp_to_dptr(context->envp)); // concat with path
	exit_by_errno(errno, cmd.cmd[0]);
}

pid_t	exec_fork_pipe(t_cmd cmd, t_context *context, t_in_out *in_out)
{
	pid_t	pid;
	int		outpipe[2];

	if (!ft_pipe(outpipe))
		return (-1);
	pid = fork();
	if (pid == -1)
		return (pid);
	if (!pid)
		child(cmd, context, in_out, outpipe);
	close(outpipe[1]);
	close(in_out->infile);
	in_out->infile = outpipe[0];
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
		if (in_out->infile && !ft_dup2(in_out->infile, 0))
			exit(1);
		if (in_out->infile != 0)
			close(in_out->infile);
		if (!ft_dup2(in_out->outfile, 1))
			exit(1);
		if (in_out->outfile != 1)
			close(in_out->outfile);
		check_cmd_type(&cmd, context, in_out, NULL);
		execve(cmd.cmd[0], cmd.cmd, convert_envp_to_dptr(context->envp));
		exit_by_errno(errno, cmd.cmd[0]);
	}
	close(in_out->infile);
	close(in_out->outfile);
	return (pid);
}
