/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:23:31 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/07 14:29:18 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>

char	*expand_asterisk_helper(char **list)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		i;

	i = -1;
	tmp2 = NULL;
	while (list[++i] != NULL)
	{
		if (ft_strncmp(list[i], " ", 1) != 0)
		{
			tmp = ft_strjoin(list[i], " ");
			if (tmp2)
			{
				tmp3 = ft_strjoin(tmp2, tmp);
				safe_free((void **) &tmp2);
				tmp2 = tmp3;
			}
			else
				tmp2 = ft_strjoin(tmp2, tmp);
			safe_free((void **) &tmp);
		}
	}
	return (tmp2);
}

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
				break ;
			}
		}
		else
		{
			safe_free((void **) &list[*i]);
			list[(*i)++] = ft_strdup(" ");
			break ;
		}
	}
}

char	*expand_asterisk(char *arg)
{
	char	**str;
	char	*no_q;
	char	**list;
	char	*new;

	no_q = del_quote(arg);
	list = current_path_ls();
	check_side(list, no_q);
	str = ft_split(no_q, "*");
	check_str(list, str);
	new = expand_asterisk_helper(list);
	if (new)
	{
		free(arg);
		arg = new;
	}
	free_c_dptr(&str);
	free_c_dptr(&list);
	safe_free((void **) &no_q);
	return (arg);
}

int	is_asterisk(char *str)
{
	int	i;
	int	j;
	int	quote;

	i = 0;
	j = find_char(str, '*');
	if (j == -1)
		return (0);
	quote = 0;
	while (i < j)
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if ((quote == '\'' && str[i] == '\'') \
									|| (quote == '\"' && str[i] == '\"'))
			quote = 0;
		i++;
	}
	if (quote)
		return (0);
	return (1);
}

void	expand_asterisks(char ***str)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
	{
		if (is_asterisk((*str)[i]))
		{
			(*str)[i] = expand_asterisk((*str)[i]);
			(*str)[i][ft_strlen((*str)[i]) - 1] = 0;
			split_str_i(str, &i);
		}
		else
			i++;
	}
}
