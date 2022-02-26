/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parenthesis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:43:17 by jaham             #+#    #+#             */
/*   Updated: 2022/02/26 21:33:01 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "temphead.h"
#include "libft.h"
#include <stdlib.h>

static int	replace_curr_fd(t_context *context, int backup[3])
{
	backup[0] = ft_dup(context->curr_fd[0]);
	backup[1] = ft_dup(context->curr_fd[1]);
	backup[2] = ft_dup(context->curr_fd[2]);
	if (!(backup[0] != -1) && (backup[1] != -1) && (backup[2] != -1))
		return (0);
	ft_close(context->curr_fd[0]);
	ft_close(context->curr_fd[1]);
	ft_close(context->curr_fd[2]);
	return (!(
		!ft_dup2(0, context->curr_fd[0])
		|| !ft_dup2(1, context->curr_fd[1])
		|| !ft_dup2(2, context->curr_fd[2])
	));
}

static int	restore_curr_fd(t_context *context, int backup[3])
{
	ft_close(context->curr_fd[0]);
	ft_close(context->curr_fd[1]);
	ft_close(context->curr_fd[2]);
	context->curr_fd[0] = ft_dup(backup[0]);
	context->curr_fd[1] = ft_dup(backup[1]);
	context->curr_fd[2] = ft_dup(backup[2]);
	return (!((backup[0] < 0) || (backup[1] < 0) || (backup[2] < 0)));
}

void	exec_parenthesis(char *str, t_context *context)
{
	t_cmd_line	*new;
	int			backup[3];
	int			result;

	// new = parse(str, context, &result);
//test
	result = 1;
	new = malloc(sizeof(t_cmd_line));
	new->next = malloc(sizeof(t_cmd_line));
	new->type = PIPE;
	new->pipes = malloc(sizeof(t_pipe));
	new->pipes->len = 2;
	new->pipes->cmds = malloc(sizeof(t_cmd) * 2);
	new->pipes->cmds[0].type = SINGLE_CMD;
	new->pipes->cmds[0].redir = NULL;
	new->pipes->cmds[0].cmd = ft_split("cat -e", ' ');
	new->pipes->cmds[1].type = SINGLE_CMD;
	new->pipes->cmds[1].redir = NULL;
	new->pipes->cmds[1].cmd = ft_split("cat -e", ' ');

	new->next->next = NULL;
	new->next->type = AND;
	new->next->pipes = malloc(sizeof(t_pipe));
	new->next->pipes->len = 1;
	new->next->pipes->cmds = malloc(sizeof(t_cmd));
	new->next->pipes->cmds[0].type = SINGLE_CMD;
	new->next->pipes->cmds[0].redir = NULL;
	new->next->pipes->cmds[0].cmd = ft_split("ls", ' ');
//end
	if (!replace_curr_fd(context, backup))
		exit(1);
	if (result == 1)
		executor(new, context);
	else
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		exit(258);
	}
	if (!restore_curr_fd(context, backup))
		exit(1);
	exit(context->exit_status);
}
