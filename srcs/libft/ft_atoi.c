/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:12:04 by jaham             #+#    #+#             */
/*   Updated: 2022/02/14 06:15:07 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned long	ret;

	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	sign = 1 - ((*str == '-') << 1);
	str += (*str == '+' || *str == '-');
	ret = 0;
	while ('0' <= *str && *str <= '9')
	{
		if (ret > (unsigned long) LONG_MAX / 10 + (sign < 0))
			return ((sign < 0) - 1);
		ret *= 10;
		if (ret > (unsigned long) LONG_MAX - *str + '0' + (sign < 0))
			return ((sign < 0) - 1);
		ret += (*str - '0');
		str++;
	}
	return (ret * sign);
}
