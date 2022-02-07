/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:40:21 by jaham             #+#    #+#             */
/*   Updated: 2022/02/07 16:35:40 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(const char *str, char sep)
{
	size_t	i;
	size_t	temp;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		while (str[i] == sep)
			i++;
		temp = i;
		while (str[i] && (str[i] != sep))
			i++;
		if (i != temp)
			cnt++;
	}
	return (cnt);
}

static char	*get_string(const char *str, size_t i, size_t temp)
{
	char	*ret;
	size_t	len;

	len = i - temp;
	ret = ft_malloc(sizeof(char), len + 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, str + temp, len);
	ret[len] = '\0';
	return (ret);
}

void	destroy_string(char **ret)
{
	size_t	i;

	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		ret[i] = NULL;
		i++;
	}
}

static char	**split_string(char **ret, const char *str, char sep)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == sep)
			i++;
		temp = i;
		while (str[i] && (str[i] != sep))
			i++;
		if (i != temp)
		{
			ret[j] = get_string(str, i, temp);
			if (!ret[j++])
			{
				destroy_string(ret);
				return (NULL);
			}
		}
	}
	ret[j] = NULL;
	return (ret);
}

char	**ft_split(const char *str, char sep)
{
	char	**ret;
	size_t	ret_size;

	ret_size = get_size(str, sep);
	ret = ft_malloc(sizeof(char *), ret_size + 1);
	if (!ret)
		return (NULL);
	if (!split_string(ret, str, sep))
		return (NULL);
	return (ret);
}
