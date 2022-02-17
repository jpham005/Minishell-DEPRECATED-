#include <stdio.h>
#include <unistd.h>

int	main()
{
	char	str[10];

	read(0, str, 9);
	str[9] = 0;
	printf("%s\n", str);
}
