/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:20:39 by jaham             #+#    #+#             */
/*   Updated: 2022/02/18 13:52:42 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "exec.h"
#include "temphead.h"

int	is_built_in(const char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3))
		return (CD);
	if (ft_strncmp(cmd, "echo", 5))
		return (ECHO);
	if (ft_strncmp(cmd, "env", 4))
		return (ENV);
	if (ft_strncmp(cmd, "exit", 5))
		return (EXIT);
	if (ft_strncmp(cmd, "export", 7))
		return (EXPORT);
	if (ft_strncmp(cmd, "pwd", 4))
		return (PWD);
	if (ft_strncmp(cmd, "unset", 6))
		return (UNSET);
	return (NONE);
}