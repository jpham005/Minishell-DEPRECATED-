/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:58:08 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 07:59:12 by jaham            ###   ########.fr       */
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
	in_out->pipeline[0] = -1;
	in_out->pipeline[1] = -1;
}

void	close_pipes(int pipes[2])
{
	ft_close(pipes[0]);
	ft_close(pipes[1]);
}

int	handle_pipe(t_in_out *in_out, t_pipe_len_status status, t_context *context)
{
	if (in_out->prev[0] != -1)
		ft_close(in_out->prev[0]);
	if (in_out->prev[1] != -1)
		ft_close(in_out->prev[1]);
	in_out->prev[0] = in_out->curr[0];
	in_out->prev[1] = in_out->curr[1];
	if (status == IS_PIPE_CONTINUE)
		ft_pipe(in_out->curr);
	else
	{
		in_out->curr[0] = -1;
		in_out->curr[1] = -1;
	}
	return (1);
}

//#include <stdio.h>
//#include <fcntl.h>
//int	handle_pipe(t_in_out *in_out, t_pipe_len_status status, t_context *context)
//{
//	int	new_pipe[2];

//	if (in_out->pipeline[0] != -1)
//	{
//		if (!ft_dup2(in_out->pipeline[0], 0))
//		{
//			close_pipes(in_out->pipeline);
//			return (0);
//		}
//	}
//	else
//	{
//		if (!ft_dup2(context->std_fd[0], 0))
//			return (0);
//	}
//	close_pipes(in_out->pipeline);
//	if (status == IS_PIPE_END)
//		return (1);
//	if (!ft_dup2(context->std_fd[1], 1))
//		return (0);
//	if (!ft_pipe(new_pipe) || !ft_dup2(new_pipe[1], 1))
//	{
//		close_pipes(in_out->pipeline);
//		close_pipes(new_pipe);
//		return (0);
//	}
//	in_out->pipeline[0] = new_pipe[0];
//	in_out->pipeline[1] = new_pipe[1];
//	return (1);
//}
