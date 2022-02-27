/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str_asterisk.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:06:20 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 17:13:48 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

void	check_str_helper(char **list, char **str, int *i, int *arr)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = list[arr[*i]];
	while (1)
	{
		tmp = ft_strnstr(tmp, str[j], ft_strlen(tmp));
		if (tmp != NULL)
		{
			if (str[j + 1] != NULL)
				j++;
			else
			{
				(*i)++;
				break;
			}
		}
		else
		{
			*(arr + (*i)) = -2;
			(*i)++;
			break;
		}
	}
}

void	check_str(char **list, char **str, int *arr)
{
	int		i;

	i = 0;
	if (str[0] == NULL)
		return ;
	while (arr[i] != -1)
		check_str_helper(list, str, &i, arr);
}
