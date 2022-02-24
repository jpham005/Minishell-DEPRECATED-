/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:03:48 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/02/24 09:04:27 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const size_t	needle_len = ft_strlen(needle);

	if (*needle)
	{
		if (len == 0)
			return (NULL);
		while (len-- && ft_strncmp(haystack, needle, needle_len) != 0)
		{
			if (len < needle_len)
				return (NULL);
			if (*haystack == '\0')
				return (NULL);
			haystack++;
		}
	}
	return ((char *)haystack);
}