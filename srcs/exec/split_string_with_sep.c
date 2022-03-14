/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc_helper.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:54:28 by jaham             #+#    #+#             */
/*   Updated: 2022/03/12 20:05:39 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static size_t	get_size(char *str, char *sep)
{
	size_t	i;
	size_t	temp;
	size_t	cnt;

	i = 0;
	temp = 0;
	cnt = 0;
	while (str[i])
	{
		while (ft_strchr(sep, str[i]))
			i++;
		if (temp != i)
			cnt++;
		temp = i;
		while (str[i] && !ft_strchr(sep, str[i]))
			i++;
		if (i != temp)
			cnt++;
		temp = i;
	}
	return (cnt);
}

static char	*get_string(const char *str, size_t i, size_t temp)
{
	char	*ret;
	size_t	len;

	len = i - temp;
	ret = ft_malloc(sizeof(char), len + 1);
	ft_memcpy(ret, str + temp, len);
	ret[len] = '\0';
	return (ret);
}

static char	**split_string(char **ret, const char *str, const char *sep)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	i = 0;
	j = 0;
	temp = 0;
	while (str[i])
	{
		while (ft_strchr(sep, str[i]))
			i++;
		if (i != temp)
			ret[j++] = get_string(str, i, temp);
		temp = i;
		while (str[i] && !ft_strchr(sep, str[i]))
			i++;
		if (i != temp)
			ret[j++] = get_string(str, i, temp);
		temp = i;
	}
	ret[j] = NULL;
	return (ret);
}

char	**split_string_with_sep(char *str, char *sep)
{
	char	**ret;
	size_t	ret_size;

	ret_size = get_size(str, sep);
	ret = ft_malloc(sizeof(char *), ret_size + 1);
	split_string(ret, str, sep);
	return (ret);
}
