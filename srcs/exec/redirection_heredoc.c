/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:38:02 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 14:42:07 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temphead.h"
#include "exec.h"
#include "libft.h"
#include <errno.h>

int	handle_redir_heredoc(int in[2], t_redir *redir, \
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
