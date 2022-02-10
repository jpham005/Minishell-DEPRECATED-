/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_intro.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:20:11 by jaham             #+#    #+#             */
/*   Updated: 2022/02/10 11:38:22 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	print_intro(void)
{
	char	str[2000];
	int		fd;
	int		read_size;

	fd = open(ASCII_ART_PATH"aurora", O_RDONLY);
	read_size = read(fd, str, 2000);
	if (read_size < 0)
		return (0);
	if (write(STDERR_FILENO, str, read_size) < 0)
		return (0);
	return (1);
}
