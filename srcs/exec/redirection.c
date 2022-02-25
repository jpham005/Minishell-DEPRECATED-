/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:36:44 by jaham             #+#    #+#             */
/*   Updated: 2022/02/25 15:43:49 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temphead.h"
#include "exec.h"
#include "term.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

static int	handle_in(const char *target)
{
	int	fd;

	fd = open(target, O_RDONLY);
	if (fd == -1)
	{
		perror(target);
		return (0);
	}
	if (!ft_dup2(fd, 0))
		return (0);
	ft_close(fd);
	return (1);
}

static int	handle_heredoc(const char *target)
{
	int		heredoc[2];
	char	*buf;

	if (!ft_pipe(heredoc))
		return (0);
	while (1)
	{
		buf = get_next_line(0);
		if (!buf)
			return (0);
		if (!*buf)
			break ;
		if (ft_putstr_fd(buf, heredoc[1]) == -1)
		{
			safe_free((void **) &buf);
			return (0);
		}
		safe_free((void **) &buf);
	}
	safe_free((void **) &buf);
	if (!ft_dup2(heredoc[0], 0))
		return (0);
	ft_close(heredoc[0]);
	ft_close(heredoc[1]);
	return (1);
}

static int	handle_out(t_redir *redir)
{
	int	op;
	int	fd;

	if (redir->type == REDIR_OUT)
		op = O_WRONLY | O_CREAT | O_TRUNC;
	else
		op = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(redir->target, op, 0666);
	if (fd == -1)
	{
		perror(redir->target);
		return (0);
	}
	if (!ft_dup2(fd, 1))
		return (0);
	ft_close(fd);
	return (1);
}

int	handle_redir(t_redir *redir, t_context *context)
{
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (!handle_in(redir->target))
				return (0);
		}
		if (redir->type == REDIR_HEREDOC)
		{
			if (!handle_heredoc(redir->target))
				return (0);
		}
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		{
			if (!handle_out(redir))
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}
