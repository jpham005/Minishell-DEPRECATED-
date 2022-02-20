/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_by_errno.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:04:51 by jaham             #+#    #+#             */
/*   Updated: 2022/02/20 15:09:26 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <stdlib.h>

void	exit_by_errno(int status)
{
	if (status == EACCES)
	{
		write(2, "not executable\n", ft_strlen("not executable\n"));
		exit(126);
	}
	if (status == )
}
