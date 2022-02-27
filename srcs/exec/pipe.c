/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:58:08 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 09:05:51 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "temphead.h"
#include "libft.h"

void	init_in_out(t_in_out *in_out)
{
	in_out->prev[0] = -1;
	in_out->prev[1] = -1;
	in_out->curr[0] = -1;
	in_out->curr[1] = -1;
}

void	close_pipes(int pipes[2])
{
	ft_close(pipes[0]);
	ft_close(pipes[1]);
}

int	handle_pipe(t_in_out *in_out, t_pipe_bool status, t_context *context)
{
	if (in_out->prev[0] != -1)
		ft_close(in_out->prev[0]);
	if (in_out->prev[1] != -1)
		ft_close(in_out->prev[1]);
	in_out->prev[0] = in_out->curr[0];
	in_out->prev[1] = in_out->curr[1];
	if (status == DO_PIPE)
		ft_pipe(in_out->curr);
	else
	{
		in_out->curr[0] = -1;
		in_out->curr[1] = -1;
	}
	return (1);
}

int	replace_stdio(t_in_out *in_out, t_context *context)
{
	if (in_out->prev[0] == -1)
		dup2(context->std_fd[0], STDIN_FILENO);
	else
		ft_dup2(in_out->prev[0], STDIN_FILENO);
	if (in_out->curr[0] == -1)
		dup2(context->std_fd[1], STDOUT_FILENO);
	else
		ft_dup2(in_out->curr[1], STDOUT_FILENO);
	return (1);
}
