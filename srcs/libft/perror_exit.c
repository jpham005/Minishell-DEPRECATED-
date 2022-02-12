/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:32:57 by jaham             #+#    #+#             */
/*   Updated: 2022/02/12 17:33:51 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	perror_exit(const char *str, unsigned int exit_status)
{
	perror(str);
	exit(exit_status);
}
