#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main(void)
{
	char *s = strdup("hellosssss");
	printf("bef: %s\n", s);
	char *a = strdup("mandu");
	free(s);
	s = strdup(a);
	// free(a);
	printf("aft: %s\n", s);
	free(a);
	free(s);

	return (0);
}