/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:20:39 by jaham             #+#    #+#             */
/*   Updated: 2022/02/22 17:02:14 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "exec.h"
#include "temphead.h"
#include "built_in.h"
#include <stdlib.h>

void	exec_built_in(t_cmd *cmd, t_context *context)
{
	char	*cmd_str;

	cmd_str = cmd->cmd[0];
	if (!ft_strncmp(cmd_str, "cd", 3))
		exit(cd(context, (const char **) cmd->cmd));
	if (!ft_strncmp(cmd_str, "echo", 5))
		exit(echo(context, (const char **) cmd->cmd));
	if (!ft_strncmp(cmd_str, "env", 4))
		exit(env(context, (const char **) cmd->cmd));
	if (!ft_strncmp(cmd_str, "exit", 5))
		exit(built_in_exit(context, (const char **) cmd->cmd));
	if (!ft_strncmp(cmd_str, "export", 7))
		exit(export(context, (const char **) cmd->cmd));
	if (!ft_strncmp(cmd_str, "pwd", 4))
		exit(pwd(context, (const char **) cmd->cmd));
	if (!ft_strncmp(cmd_str, "unset", 6))
		exit(unset(context, (const char **) cmd->cmd));
	return ;
}