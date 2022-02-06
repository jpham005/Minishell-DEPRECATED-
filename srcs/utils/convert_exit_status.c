/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_exit_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:28:02 by jaham             #+#    #+#             */
/*   Updated: 2022/02/05 20:49:02 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	get_len(int n)
{
	size_t	ret;

	ret = 1;
	while (n > 9)
	{
		n /= 10;
		ret++;
	}
	return (ret);
}

char	*exit_status_to_a(int exit_status)
{
	char	*ret;
	size_t	len;
	size_t	i;

	if (exit_status < 0)
		return (NULL);
	len = get_len(exit_status);
	ret = ft_malloc(sizeof(char), len + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[len - 1 - i] = exit_status % 10 + '0';
		exit_status /= 10;
		i++;
	}
	return (ret);
}
