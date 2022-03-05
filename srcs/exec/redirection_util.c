/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 12:23:12 by jaham             #+#    #+#             */
/*   Updated: 2022/03/05 15:24:55 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include <string.h>

void	dup_errs(t_err_info *err_info, char *target, int status)
{
	if (!err_info->err_target)
		err_info->err_target = ft_strdup(target);
	if (!err_info->err_str)
		err_info->err_str = ft_strdup(strerror(status));
}

void	init_in_out(int in[2], int *out)
{
	in[0] = -1;
	in[1] = -1;
	*out = -1;
}

void	set_in_out(int in[2], int out, t_in_out *in_out)
{
	if (in[0] != -1)
		in_out->in = in[0];
	if (out != -1)
		in_out->out = out;
}

int	close_and_pipe(int in[2])
{
	ft_close(in[0]);
	ft_close(in[1]);
	return (ft_pipe(in));
}

int	is_heredoc_str(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (s1[i] == 0);
}
