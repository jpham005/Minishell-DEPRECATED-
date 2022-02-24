/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:20:39 by jaham             #+#    #+#             */
/*   Updated: 2022/02/24 15:40:40 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "exec.h"
#include "temphead.h"
#include "built_in.h"
#include <stdlib.h>

int	exec_built_in(t_cmd cmd, t_context *context, t_isexit isexit)
{
	char	*cmd_str;
	int		ret;

	cmd_str = cmd.cmd[0];
	if (!ft_strncmp(cmd_str, "cd", 3))
		ret = cd(context, (const char **) cmd.cmd);
	else if (!ft_strncmp(cmd_str, "echo", 5))
		ret = echo(context, (const char **) cmd.cmd);
	else if (!ft_strncmp(cmd_str, "env", 4))
		ret = env(context, (const char **) cmd.cmd);
	else if (!ft_strncmp(cmd_str, "exit", 5))
		ret = built_in_exit(context, (const char **) cmd.cmd);
	else if (!ft_strncmp(cmd_str, "export", 7))
		ret = export(context, (const char **) cmd.cmd);
	else if (!ft_strncmp(cmd_str, "pwd", 4))
		ret = pwd(context, (const char **) cmd.cmd);
	else if (!ft_strncmp(cmd_str, "unset", 6))
		ret = unset(context, (const char **) cmd.cmd);
	else
		return (NOT_BUILT_IN);
	if (isexit == RETURN)
		return (ret);
	exit (ret);
}