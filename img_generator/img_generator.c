/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:27:07 by jaham             #+#    #+#             */
/*   Updated: 2022/02/02 02:12:32 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int		origin;
	int		outfile;
	int		read_size;
	char	buf[100000];

	origin = open("../imgs/aurora_original", O_RDONLY);
	outfile = open("../imgs/aurora", O_WRONLY | O_CREAT, 0666);
	read(origin, buf, 100000);
	write(outfile, "\033[38;5;214m", 11);
	write(outfile, buf, 1621);
	write(outfile, "\033[38;5;210m", 11);
	write(outfile, buf + 1621, 37);
	write(outfile, "\033[38;5;214m", 11);
	write(outfile, buf + 1621 + 37, 79);
	write(outfile, "\033[m", 3);
	write(outfile, "\n", 1);
	close(outfile);
	outfile = open("../imgs/aurora", O_RDONLY);
	read_size = read(outfile, buf, 10000);
	write(1, buf, read_size);
	return (0);
}
