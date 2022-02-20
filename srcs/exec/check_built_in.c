/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:20:39 by jaham             #+#    #+#             */
/*   Updated: 2022/02/20 15:49:23 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "exec.h"
#include "temphead.h"

int	is_built_in(const char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3))
		return (SH_CD);
	if (ft_strncmp(cmd, "echo", 5))
		return (SH_ECHO);
	if (ft_strncmp(cmd, "env", 4))
		return (SH_ENV);
	if (ft_strncmp(cmd, "exit", 5))
		return (SH_EXIT);
	if (ft_strncmp(cmd, "export", 7))
		return (SH_EXPORT);
	if (ft_strncmp(cmd, "pwd", 4))
		return (SH_PWD);
	if (ft_strncmp(cmd, "unset", 6))
		return (SH_UNSET);
	return (SH_NONE);
}