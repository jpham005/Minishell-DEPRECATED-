/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_intro.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:20:11 by jaham             #+#    #+#             */
/*   Updated: 2022/02/02 01:52:11 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_intro.h"

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
//ESC[38:5:⟨n⟩m Select foreground color
//ESC[48:5:⟨n⟩m Select background color
//ESC[ 38;2;⟨r⟩;⟨g⟩;⟨b⟩ m Select RGB foreground color
//ESC[ 48;2;⟨r⟩;⟨g⟩;⟨b⟩ m Select RGB background color