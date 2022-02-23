#include "include/temphead.h"
#include "include/terminal.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "srcs/libft/libft.h"
#include <stdio.h>
#include <string.h>

int main()
{
	open("infile", 0);
	printf("%d\n", fcntl(3, F_GETFD));
}
