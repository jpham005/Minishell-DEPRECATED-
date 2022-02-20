#include "include/temphead.h"
#include "include/terminal.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "srcs/libft/libft.h"
#include <stdio.h>

int main()
{
	close(0);
	printf("%d\n", fcntl(0, F_GETFD));
}
