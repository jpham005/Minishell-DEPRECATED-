/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:05:39 by jaham             #+#    #+#             */
/*   Updated: 2022/02/26 19:38:16 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/wait.h>

int	wait_all(pid_t *pids, size_t i, int ret)
{
	size_t	j;
	int		status;

	j = 0;
	while (i-- > 1)
	{
		if (pids[j] != -1)
			ft_waitpid(pids[j], NULL, 0);
		j++;
	}
	if (pids[j] != -1)
		ft_waitpid(pids[j], &status, 0);
	free(pids);
	if (ret)
		return (ret);
	if (ft_wifexited(status))
		return (ft_wexitstatus(status));
	if (ft_wifsignaled(status))
		return (ft_wtermsig(status) + 128);
	return (status % 128);
}
