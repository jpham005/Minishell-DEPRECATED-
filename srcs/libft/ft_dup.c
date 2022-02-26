/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:44:18 by jaham             #+#    #+#             */
/*   Updated: 2022/02/26 21:03:19 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_dup(int fd)
{
	int	ret;

	ret = dup(fd);
	if (ret < 0)
	{
		perror("dup");
		return (-1);
	}
	return (ret);
}