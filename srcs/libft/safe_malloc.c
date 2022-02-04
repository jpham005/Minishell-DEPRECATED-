/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:29:40 by jaham             #+#    #+#             */
/*   Updated: 2022/02/04 11:10:22 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	safe_malloc(void **ptr, size_t size, size_t n)
{
	*ptr = malloc(size * n);
	if (!*ptr)
	{
		perror("Malloc");
		return (0);
	}
	return (1);
}
