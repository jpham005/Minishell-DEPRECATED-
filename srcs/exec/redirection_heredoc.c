/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:38:02 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 21:49:07 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/signal.h>

void	heredoc_parent_handler(int sig)
{
	if (sig == SIGINT)
	{
		return ;
	}
}

void	heredoc_child(int in[2], t_redirect *redir, t_context *context)
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
			exit(1);
		safe_free((void **) &buf);
	}
	safe_free((void **) &buf);
	exit(0);
}

int	handle_redir_heredoc(int in[2], t_redirect *redir, \
										t_err_info *info, t_context *context)
{
	int		status;
	pid_t	pid;

	signal(SIGINT, heredoc_parent_handler);
	pid = fork();
	if (pid == -1)
		return (0);
	if (!pid)
		heredoc_child(in, redir, context);
	waitpid(pid, &status, 0);
	if (ft_wexitstatus(status) == 1)
	{
		ft_strdup_err(info->err_str, "error while heredoc\n");
		ft_strdup_err(info->err_target, redir->target);
		signal(SIGINT, sig_int_handler_exec);
		return (0);
	}
	if (ft_wexitstatus(status) == 2)
		return (-1);
	signal(SIGINT, sig_int_handler_exec);
	return (1);
}
