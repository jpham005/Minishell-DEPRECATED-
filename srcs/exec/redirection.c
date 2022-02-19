/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:42:47 by jaham             #+#    #+#             */
/*   Updated: 2022/02/19 21:20:18 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temphead.h"
#include "libft.h"
#include <fcntl.h>

int	handle_inpipe(int in[2], t_redirect *redir, int type, char *target)
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
