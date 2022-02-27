/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:51:36 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 21:33:40 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include <stdlib.h>

static void	child(t_cmd *cmd, t_context *context, \
											t_in_out *in_out, int pipeline[2])
{
	t_sh_built_in	built_in_type;

	if (in_out->in != 0)
	{
		if (!ft_dup2(in_out->in, 0))
			exit(1);
		ft_close(in_out->in);
	}
	if (in_out->out == 1 && !ft_dup2(pipeline[1], 1))
		exit(1);
	else if (in_out->out > 1)
	{
		if (!ft_dup2(in_out->out, 1))
			exit(1);
		ft_close(in_out->out);
	}
	ft_close(pipeline[0]);
	ft_close(pipeline[1]);
	built_in_type = is_built_in(cmd->cmd[0]);
	if (built_in_type != SH_NOT_BUILT_IN)
		exit(exec_built_in(cmd->cmd, context, built_in_type));
	if (cmd->type == SINGLE_CMD)
		exec_cmd(cmd->cmd, context);
	else
		exec_parenthesis(cmd->cmd[0], context, in_out);
}

pid_t	exec_fork(t_cmd *cmd, t_context *context, t_in_out *in_out)
{
	pid_t			pid;
	int				pipeline[2];

	if (!ft_pipe(pipeline))
		return (-1);
	pid = fork();
	if (pid == -1)
		return (pid);
	if (!pid)
		child(cmd, context, in_out, pipeline);
	ft_close(pipeline[1]);
	ft_close(in_out->in);
	in_out->in = pipeline[0];
	in_out->out = 1;
	return (pid);
}

static void	child_out(t_cmd *cmd, t_context *context, t_in_out *in_out)
{
	t_sh_built_in	built_in_type;

	if (in_out->in != 0)
	{
		if (!ft_dup2(in_out->in, 0))
			exit(1);
		ft_close(in_out->in);
	}
	if (in_out->out > 1)
	{
		if (!ft_dup2(in_out->out, 1))
			exit(1);
		ft_close(in_out->in);
	}
	built_in_type = is_built_in(cmd->cmd[0]);
	if (built_in_type != SH_NOT_BUILT_IN)
		exit(exec_built_in(cmd->cmd, context, built_in_type));
	if (cmd->type == SINGLE_CMD)
		exec_cmd(cmd->cmd, context);
	else
		exec_parenthesis(cmd->cmd[0], context, in_out);
}

pid_t	exec_fork_out(t_cmd *cmd, t_context *context, t_in_out *in_out)
{
	pid_t			pid;

	pid = fork();
	if (pid == -1)
		return (pid);
	if (!pid)
		child_out(cmd, context, in_out);
	ft_close(in_out->in);
	in_out->in = 0;
	in_out->out = 1;
	return (pid);
}
