/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:16:00 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 21:48:34 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <stdlib.h>

void	clear_redirect(t_redirect *redir)
{
	t_redirect	*temp;

	while (redir)
	{
		free(redir->target);
		temp = redir->next;
		free(redir);
		redir = temp;
	}
}

void	clear_cmds(t_cmd *cmd)
{
	free_c_dptr(&(cmd->cmd));
	clear_redirect(cmd->redir);
}

void	clear_pipe_line(t_pipe *pipes)
{
	size_t	i;

	i = 0;
	while (i < pipes->len)
	{
		clear_cmds(&(pipes->cmds[i]));
		i++;
	}
	free(pipes->cmds);
}

void	clear_cmd_line(t_cmd_line **head)
{
	t_cmd_line	*cp;
	t_cmd_line	*temp;

	cp = *head;
	while (cp)
	{
		clear_pipe_line(cp->pipes);
		temp = cp->next;
		free(cp);
		cp = temp;
	}
	*head = NULL;
}
