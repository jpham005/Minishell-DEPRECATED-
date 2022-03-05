/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:38:02 by jaham             #+#    #+#             */
/*   Updated: 2022/03/05 15:23:37 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include <stdlib.h>

void	heredoc_child(int in[2], t_redirect *redir, t_context *context)
{
	char	*buf;
	char	*temp;

	if (!ft_dup2(context->std_fd[0], 0) || !ft_dup2(context->std_fd[1], 1))
		exit(1);
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

int	handle_redir_heredoc(int in[2], t_redirect *redir, t_context *context)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (0);
	if (!pid)
		heredoc_child(in, redir, context);
	waitpid(pid, &status, 0);
	if (ft_wexitstatus(status) == 1)
		return (0);
	if (ft_wexitstatus(status) == 2)
		return (-1);
	return (1);
}
