/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:42:47 by jaham             #+#    #+#             */
/*   Updated: 2022/02/21 21:14:45 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temphead.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "exec.h"

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

static int	handle_redir_heredoc(int in[2], t_redirect *redir, \
										t_err_info *info, t_context *context)
{
	char	*buf;
	char	*temp;

	while (1)
	{
		buf = ft_readline(context, "> ");
		if (!buf)
			break ;
		if (is_heredoc_str(buf, redir->target))
			break ;
		temp = buf;
		buf = ft_strjoin(buf, "\n");
		safe_free((void **) &temp);
		if (ft_putstr_fd(buf, in[1]) == -1)
		{
			dup_errs(info, "heredoc", errno);
			return (0);
		}
		safe_free((void **) &buf);
	}
	safe_free((void **) &buf);
	return (1);
}

static int	handle_in(int in[2], t_redirect *redir, \
										t_err_info *inf, t_context *context)
{
	int		fd;
	char	*buf;
	int		ret;

	ret = 1;
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (!close_and_pipe(in))
				return (0);
			if (!handle_redir_in(in, redir, inf))
				ret = 0;
		}
		else if (redir->type == REDIR_HEREDOC)
		{
			if (!close_and_pipe(in))
				return (0);
			if (!handle_redir_heredoc(in, redir, inf, context))
				ret = 0;
		}
		redir = redir->next;
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

int	handle_redirection(t_redirect *redir, t_in_out *in_out, t_context *context)
{
	int			in[2];
	int			out;
	int			ret;
	t_err_info	err_info;

	if (!redir)
		return (1); // need initialize in[2], out. decide when to pipe
	init_in_out(in, &out);
	ret = 1;
	err_info.err_target = NULL;
	err_info.err_str = NULL;
	if (!handle_in(in, redir, &err_info, context))
		ret = 0;
	if (!handle_out(&out, redir, &err_info))
		ret = 0;
	close(in[1]);
	set_in_out(in, out, in_out);
	return (ret);
}
