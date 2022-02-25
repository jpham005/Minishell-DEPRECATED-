/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:09:27 by jaham             #+#    #+#             */
/*   Updated: 2022/02/25 17:57:45 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term.h"
#include "exec.h"
#include "temphead.h"
#include "libft.h"
#include <errno.h>

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
		safe_free((void **) temp);
		safe_free((void **) ret);
		i++;
	}
	return (ret);
}
//not found 127  
int	check_cmd(char *cmd)
{
	t_stat	stat;

	if (lstat(cmd, &stat) == -1)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
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
		if (stat == NOT_FOUND || IS_DIR || NO_PERMISSION)
			exit_with_cmd_err(cmd, stat);
		execve(cmd[0], cmd, convert_envp_to_dptr(context->envp));
		exit_by_errno(errno, cmd[0]);
	}
	if (cmd[0][0] == '\0')
	{
		ft_putstr_fd(SHELL_NAME);
		ft_putstr_fd(cmd[0], 2);
	}
	cmd_exec = try_cmd(cmd, context);
	if (!cmd_exec)
		execve(cmd[0], cmd, convert_envp_to_dptr(context->envp));
	else
		execve(cmd_exec, cmd, convert_envp_to_dptr(context->envp));
}
