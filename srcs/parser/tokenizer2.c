/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:51:13 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/07 15:52:22 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h> 

int	ft_free_str(char **str)
{
	if (!str || !(*str))
		return (0);
	free(*str);
	*str = NULL;
	return (1);
}

int	ft_free_doublestr(char ***doublestr_addr)
{
	int		i;
	char	**doublestr;

	if (!doublestr_addr || !(*doublestr_addr))
		return (0);
	i = -1;
	doublestr = *doublestr_addr;
	while (doublestr[++i])
		ft_free_str(&doublestr[i]);
	free(doublestr);
	*doublestr_addr = 0;
	return (1);
}

int	ft_len_doublestr(char **str)
{
	int	idx;

	idx = 0;
	if (!str || !(*str))
		return (0);
	while (*str++)
		idx++;
	return (idx);
}

void	ft_realloc_doublestr(char ***strs_ref, char *item)
{
	char	**ret;
	char	**strs;
	int		len;

	strs = *strs_ref;
	if (!item)
		return ;
	len = ft_len_doublestr(strs) + 2;
	ret = (char **)ft_calloc(sizeof(char *), len--);
	ret[--len] = ft_strdup(item);
	while (len--)
		ret[len] = ft_strdup(strs[len]);
	*strs_ref = ret;
	ft_free_doublestr(&strs);
}

int	ft_is_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
