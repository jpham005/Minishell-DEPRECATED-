/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:09:27 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 21:48:55 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

char	*try_cmd(char **cmd, t_context *context)
{
	t_stat	stat;
	char	*temp;
	char	*ret;
	char	**path;
	size_t	i;

	path = ft_split(find_list_by_key(context->envp, "PATH")->value, ':');
	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		ret = ft_strjoin(temp, cmd[0]);
		if (lstat(ret, &stat) != -1)
		{
			safe_free((void **) &temp);
			break ;
		}
		safe_free((void **) &temp);
		safe_free((void **) &ret);
		i++;
	}
	return (ret);
}

int	check_cmd(char *cmd)
{
	t_stat	stat;

	if (lstat(cmd, &stat) == -1)
		return (NOT_FOUND);
	if (stat.st_mode & S_IFDIR)
		return (IS_DIR);
	if (stat.st_mode & S_IXUSR)
		return (NO_PERMISSION);
	return (-1);
}

void	exit_with_cmd_err(char *cmd, int stat)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(cmd, 2);
	if (stat == NOT_FOUND)
	{
		ft_putstr_fd(NOT_FOUND_ERR_MSG, 2);
		exit(127);
	}
	if (stat == IS_DIR)
	{
		ft_putstr_fd(IS_DIR_ERR_MSG, 2);
		exit(126);
	}
	else if (stat == NO_PERMISSION)
	{
		ft_putstr_fd(PERMISSION_ERR_MSG, 2);
		exit(126);
	}
}

void	exec_cmd(char **cmd, t_context *context)
{
	char	*cmd_exec;
	int		stat;

	if (ft_strchr(cmd[0], '/'))
	{
		stat = check_cmd(cmd[0]);
		if (stat == NOT_FOUND || stat == IS_DIR || stat == NO_PERMISSION)
			exit_with_cmd_err(cmd[0], stat);
		execve(cmd[0], cmd, convert_envp_to_dptr(context->envp));
		exit_by_errno(errno, cmd[0]);
	}
	if (cmd[0][0] == '\0')
		exit_with_msg(cmd[0], CMD_NOT_FOUND_ERR_MSG, 127);
	cmd_exec = try_cmd(cmd, context);
	if (!cmd_exec)
		exit_with_msg(cmd[0], CMD_NOT_FOUND_ERR_MSG, 127);
	else
		execve(cmd_exec, cmd, convert_envp_to_dptr(context->envp));
	exit_with_msg(cmd[0], strerror(errno), 126);
}
