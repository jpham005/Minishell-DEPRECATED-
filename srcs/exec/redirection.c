/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:36:44 by jaham             #+#    #+#             */
/*   Updated: 2022/03/06 12:58:16 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
static int	handle_redir_in(int in[2], t_redirect *redir, t_err_info *err_info)
{
	int		fd;
	char	*buf;

	fd = open(redir->target, O_RDONLY);
	if (fd == -1)
	{
		dup_errs(err_info, redir->target, errno);
		return (0);
	}
	while (1)
	{
		buf = get_next_line(fd);
		if (!ft_strncmp(buf, "", 1))
			break ;
		if (ft_putstr_fd(buf, in[1]) == -1)
		{
			dup_errs(err_info, redir->target, errno);
			return (0);
		}
		free(buf);
	}
	safe_free((void **) &buf);
	return (1);
}

static int	handle_in(int in[2], t_redirect *r, t_err_info *inf, t_context *ctx)
{
	int		ret;
	int		here;

	ret = 1;
	while (r)
	{
		if (r->type == REDIR_IN)
		{
			if (!close_and_pipe(in))
				return (0);
			if (!handle_redir_in(in, r, inf))
				ret = 0;
		}
		else if (r->type == REDIR_HEREDOC)
		{
			if (!close_and_pipe(in))
				return (0);
			here = handle_redir_heredoc(in, r, ctx);
			if (here <= 0)
				ret = here;
		}
		r = r->next;
	}
	return (ret);
}

int	handle_out(int *out, t_redirect *redir, t_err_info *err_info)
{
	int	op;
	int	ret;

	ret = 1;
	while (redir)
	{
		if (redir->type == REDIR_OUT)
			op = O_WRONLY | O_CREAT | O_TRUNC;
		else if (redir->type == REDIR_APPEND)
			op = O_WRONLY | O_CREAT | O_APPEND;
		else
		{
			redir = redir->next;
			continue ;
		}
		*out = open(redir->target, op, 0666);
		if (*out == -1)
		{
			ret = 0;
			if (!(err_info->err_target))
				dup_errs(err_info, redir->target, errno);
		}
		redir = redir->next;
	}
	return (ret);
}

static int	print_err_redir(t_err_info *err_info, int ret)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(err_info->err_target, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_info->err_str, 2);
	ft_putstr_fd("\n", 2);
	free_err_info(err_info);
	return (ret);
}

int	handle_redirection(t_redirect *redir, t_context *context, t_in_out *in_out)
{
	int			in[2];
	int			out;
	int			ret;
	int			here;
	t_err_info	err_info;

	if (!redir)
		return (1);
	init_in_out(in, &out);
	ret = 1;
	err_info.err_target = NULL;
	err_info.err_str = NULL;
	here = handle_in(in, redir, &err_info, context);
	if (here == -1)
		return (-1);
	if (!here || !handle_out(&out, redir, &err_info))
		ret = 0;
	close(in[1]);
	if (ret == 0 && err_info.err_target)
		return (print_err_redir(&err_info, ret));
	set_in_out(in, out, in_out);
	free_err_info(&err_info);
	return (ret);
}
