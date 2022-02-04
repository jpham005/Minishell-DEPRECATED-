/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_exit_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:28:02 by jaham             #+#    #+#             */
/*   Updated: 2022/02/04 11:16:33 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert_exit_status.h"
#include "libft.h"

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
	if (!safe_malloc((void **) &ret, sizeof(char), len + 1))
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
