/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:38:02 by jaham             #+#    #+#             */
/*   Updated: 2022/03/12 20:04:25 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include <stdlib.h>

static void	expand_dollar(char **split_buf, size_t i, t_context *context)
{
	char		*new;
	char		*key;
	t_envp_list	*key_list;
	size_t		is_dollar;

	is_dollar = 0;
	while (split_buf[i][is_dollar] != '$')
		is_dollar++;
	if (split_buf[i][is_dollar + 1] == '\0')
		return ;
	key = ft_strdup(split_buf[i] + is_dollar + 1);
	key_list = find_list_by_key(context->envp, key);
	safe_free((void **) &key);
	if (!key_list)
		new = ft_substr(split_buf[i], 0, is_dollar);
	else
	{
		new = ft_malloc(sizeof(char), is_dollar + ft_strlen(key_list->value));
		ft_memcpy(new, split_buf[i], is_dollar);
		ft_memcpy(new + is_dollar, key_list->value, ft_strlen(key_list->value));
		new[is_dollar + ft_strlen(key_list->value)] = '\0';
	}
	free(split_buf[i]);
	split_buf[i] = new;
}

static void	copy_to_buf(char **buf, char **split_buf, size_t new_len)
{
	size_t	i;
	size_t	curr_len;

	*buf = ft_malloc(sizeof(char), new_len + 1);
	i = 0;
	curr_len = 0;
	while (split_buf[i])
	{
		ft_memcpy(*buf + curr_len, split_buf[i], ft_strlen(split_buf[i]));
		curr_len += ft_strlen(split_buf[i]);
		i++;
	}
	(*buf)[new_len] = '\0';
}

static void	expand_buf(char **buf, t_context *context)
{
	char	**split_buf;
	size_t	new_len;
	size_t	i;

	split_buf = split_string_with_sep(*buf, " \t\n\"\'");
	free(*buf);
	new_len = 0;
	i = 0;
	while (split_buf[i])
	{
		if (ft_strchr(split_buf[i], '$'))
			expand_dollar(split_buf, i, context);
		new_len += ft_strlen(split_buf[i]);
		i++;
	}
	copy_to_buf(buf, split_buf, new_len);
}

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
		if (ft_strchr(buf, '$'))
			expand_buf(&buf, context);
		temp = ft_strjoin(buf, "\n");
		safe_free((void **) &buf);
		buf = temp;
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

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	pid = ft_fork();
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
