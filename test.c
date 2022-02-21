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
	char *args[] = {
		"/bin/echo",
		NULL
	};
	execve("/bin/echo", args, NULL);
}
