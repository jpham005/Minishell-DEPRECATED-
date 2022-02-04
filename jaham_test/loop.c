#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

void	sig_quit(int sig)
{
	write(1, "quittttt\n", 10);
	exit (128 + sig);
}

int	main(void)
{
	int	i;

	i = 1;
	while (i < 100000000)
	{
		usleep(1000);
		if (i % 100 == 0)
		{
			write(1, "asdf", 4);
		}
		i++;
	}
}
