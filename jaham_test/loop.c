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
	while (1);
}
