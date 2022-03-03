#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct hyeonjun
{
	char **a;
};

int	main(void)
{
	int i = 0;
	struct hyeonjun *hj;

	hj = (struct hyeonjun *)malloc(sizeof(struct hyeonjun) * 3);
	// while (i < 3)
	// {
	// 	hj[i] = (struct hyeonjun *)malloc(sizeof(struct hyeonjun));
	// 	i++;
	// }
	printf("0 %p\n", hj[0]);
	printf("1 %p\n", hj[1]);
	printf("2 %p\n", hj[2]);

	return (0);
}

// int	main(void)
// {
// 	char *s = strdup("hellosssss");
// 	printf("bef: %s\n", s);
// 	char *a = strdup("mandu");
// 	free(s);
// 	s = strdup(a);
// 	// free(a);
// 	printf("aft: %s\n", s);
// 	free(a);
// 	free(s);

// 	return (0);
// }