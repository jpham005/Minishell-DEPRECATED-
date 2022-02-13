/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:12:04 by jaham             #+#    #+#             */
/*   Updated: 2022/02/13 21:00:21 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned long	ret;
	unsigned long	temp;

	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	sign = 1 - ((*str == '-') << 1);
	str += (*str == '+' || *str == '-');
	ret = 0;
	while ('0' <= *str && *str <= '9')
	{
		temp = ret * 10 + (*str - '0');
		if (temp > (unsigned long) LONG_MAX + (sign < 0) || ret > temp)
			return (-1 + (sign < 0));
		ret = temp;
		str++;
	}
	return (ret * sign);
}
