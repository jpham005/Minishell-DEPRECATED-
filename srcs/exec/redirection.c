/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:36:44 by jaham             #+#    #+#             */
/*   Updated: 2022/02/26 17:45:22 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temphead.h"
#include "exec.h"
#include "term.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

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

static int handle_heredoc(char *limit, t_context *context)
{
	int		hpipe[2];
	char	*buf;
	char	*temp;

	if (!ft_pipe(hpipe))
		return (0);
	while (1)
	{
		buf = ft_readline(context, "> ");
		if (!buf || !ft_strncmp(buf, limit, ft_strlen(limit) + 1))
			break ;
		temp = ft_strjoin(buf, "\n");
		free(buf);
		buf = temp;
		write(hpipe[1], buf, ft_strlen(buf));
		free(buf);
	}
	safe_free((void **) &buf);
	if (!ft_dup2(hpipe[0], 0))
		return (0);
	ft_close(hpipe[1]);
	ft_close(hpipe[0]);
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
			if (!handle_heredoc(redir->target, context))
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
