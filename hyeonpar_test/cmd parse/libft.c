#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (dst == NULL || src == NULL)
		return (0);
	if (dstsize == 0)
		return (strlen(src));
	while (src[len] != '\0')
		len++;
	if (dstsize != 0)
	{
		while (i < (dstsize - 1) && *(src + i) != '\0')
		{
			*(dst + i) = *(src + i);
			i++;
		}
		*(dst + i) = '\0';
	}
	return (len);
}

int		count_words(char const *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

char	*init_str(char const *s, char c)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(ptr = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ft_strlcpy(ptr, s, i + 1);
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		strs_len;
	char	**ptr;

	if (!s)
		return (NULL);
	strs_len = count_words(s, c);
	if (!(ptr = (char **)malloc(sizeof(char *) * (strs_len + 1))))
		return (NULL);
	i = -1;
	while (++i < strs_len)
	{
		while (s[0] == c)
			s++;
		if (!(ptr[i] = init_str(s, c)))
		{
			while (i > 0)
				free(ptr[i--]);
			free(ptr);
			return (NULL);
		}
		s = s + strlen(ptr[i]);
	}
	ptr[i] = 0;
	return (ptr);
}