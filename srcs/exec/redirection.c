/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:42:47 by jaham             #+#    #+#             */
/*   Updated: 2022/02/20 14:53:24 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temphead.h"
#include "libft.h"
#include <fcntl.h>

static int	handle_inpipe(int in[2], t_redirect *redir, int type, char *target)
{
	int		fd;
	char	*buf;

	fd = 0;
	if (type == REDIR_IN)
		fd = open(target, O_RDONLY);
	while (1)
	{
		buf = get_next_line(fd);
		if (!ft_strncmp(buf, "", 1) && type == REDIR_IN)
			break ;
		if (
			!ft_strncmp(buf, target, ft_strlen(target + 1)) == "\n"
			&& type == REDIR_HEREDOC
		)
			break ;
		if (ft_putstr_fd(buf, in[1]) == -1)
			return (0);
		free(buf);
	}
	safe_free((void **) &buf);
	return (1);
}

int	handle_out(int *out, t_redirect *redir)
{
	int	op;

	if (redir->type == REDIR_OUT)
		op = O_WRONLY | O_CREAT | O_TRUNC;
	else
		op = O_WRONLY | O_CREAT | O_APPEND;
	*out = open(redir->target, op, 0666);
	return (*out != -1);
}

int	handle_redirection(t_redirect *redir, int in[2], int *out)
{
	if (pipe(in) == -1)
	{
		perror("pipe");
		return (0);
	}
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			if (!handle_inpipe(in, redir, redir->type, redir->target))
				return (0);
		else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			if (!handle_out(out, redir))
				return (0);
		redir = redir->next;
	}
	close(in[1]);
	return (1);
}
