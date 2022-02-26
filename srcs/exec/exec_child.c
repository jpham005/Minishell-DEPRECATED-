/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 12:51:36 by jaham             #+#    #+#             */
/*   Updated: 2022/02/26 21:02:07 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temphead.h"
#include "exec.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>

void	child(t_cmd *cmd, t_context *context, t_in_out *in_out)
{
	if (in_out->prev[0] != -1)
	{
		if (!ft_dup2(in_out->prev[0], 0))
			exit(1);
		ft_close(in_out->prev[0]);
	}
	if (!ft_dup2(in_out->curr[1], 1))
		exit(1);
	ft_close(in_out->curr[0]);
	ft_close(in_out->curr[1]);
	if (!handle_redir(cmd->redir, context))
		exit(1);
	if (cmd->type == SINGLE_CMD)
		exec_cmd(cmd->cmd, context);
	exec_parenthesis(cmd->cmd[0], context);
}

pid_t	exec_out(t_cmd *cmd, t_context *context, t_in_out *in_out)
{
	pid_t			pid;
	t_sh_built_in	built_in_type;

	pid = fork();
	if (pid == -1)
		return (pid);
	if (!pid)
	{
		if (in_out->prev[0] != -1)
		{
			if (!ft_dup2(in_out->prev[0], 0))
				exit(1);
			ft_close(in_out->prev[0]);
		}
		built_in_type = is_built_in(cmd->cmd[0]);
		if (built_in_type != SH_NOT_BUILT_IN)
			exit(exec_built_in(cmd->cmd, context, built_in_type));
		if (cmd->type == SINGLE_CMD)
			exec_cmd(cmd->cmd, context);
		else
			exec_parenthesis(cmd->cmd[0], context);
		exit_by_errno(errno, cmd->cmd[0]);
	}
	ft_close(in_out->prev[0]);
	return (pid);
}
