/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:17:17 by jaham             #+#    #+#             */
/*   Updated: 2022/03/07 11:58:45 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

t_sh_built_in	is_built_in(char **cmd)
{
	if (!cmd)
		return (SH_NOT_BUILT_IN);
	if (!ft_strncmp(cmd[0], "cd", ft_strlen("cd") + 1))
		return (SH_CD);
	if (!ft_strncmp(cmd[0], "echo", ft_strlen("echo") + 1))
		return (SH_ECHO);
	if (!ft_strncmp(cmd[0], "env", ft_strlen("env") + 1))
		return (SH_ENV);
	if (!ft_strncmp(cmd[0], "exit", ft_strlen("exit") + 1))
		return (SH_EXIT);
	if (!ft_strncmp(cmd[0], "export", ft_strlen("export") + 1))
		return (SH_EXPORT);
	if (!ft_strncmp(cmd[0], "pwd", ft_strlen("pwd") + 1))
		return (SH_PWD);
	if (!ft_strncmp(cmd[0], "unset", ft_strlen("unset") + 1))
		return (SH_UNSET);
	return (SH_NOT_BUILT_IN);
}

int	exec_built_in(char **cmd, t_context *context, t_sh_built_in type)
{
	if (type == SH_CD)
		return (cd(context, (const char **) cmd));
	if (type == SH_ECHO)
		return (echo(context, (const char **) cmd));
	if (type == SH_ENV)
		return (env(context, (const char **) cmd));
	if (type == SH_EXIT)
		return (built_in_exit(context, (const char **) cmd));
	if (type == SH_EXPORT)
		return (export(context, (const char **) cmd));
	if (type == SH_PWD)
		return (pwd(context, (const char **) cmd));
	if (type == SH_UNSET)
		return (unset(context, (const char **) cmd));
	return (1);
}
