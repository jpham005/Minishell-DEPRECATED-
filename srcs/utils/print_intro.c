/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_intro.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:20:11 by jaham             #+#    #+#             */
/*   Updated: 2022/03/07 13:13:32 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

int	print_intro(void)
{
	char	str[2000];
	int		fd;
	int		read_size;

	// fd = open(ASCII_ART_PATH"aurora", O_RDONLY);
	fd = open("/Users/hyeonpar/Desktop/Minishell/imgs/aurora", O_RDONLY);
	read_size = read(fd, str, 2000);
	if (read_size < 0)
		return (0);
	if (write(2, str, read_size) < 0)
		return (0);
	return (1);
}
