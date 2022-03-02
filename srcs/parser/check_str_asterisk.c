/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str_asterisk.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:06:20 by jaham             #+#    #+#             */
/*   Updated: 2022/03/02 01:13:43 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

void	check_str_helper(char **list, char **str, int *i)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = list[*i];
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
			safe_free((void **) &list[*i]);
			list[*i] = ft_strdup(" ");
			(*i)++;
			break;
		}
	}
}

void	check_str(char **list, char **str)
{
	int		i;

	i = 0;
	if (str[0] == NULL)
		return ;
	while (list[i] != NULL)
		check_str_helper(list, str, &i);
}
