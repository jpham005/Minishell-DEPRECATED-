/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisks_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 17:52:30 by jaham             #+#    #+#             */
/*   Updated: 2022/03/11 20:22:29 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	set_values_str_helper(int *expanded, int *j)
{
	*expanded = 1;
	(*j)++;
}

void	check_str(char **list, char **str, int *expanded)
{
	int		i;

	i = 0;
	if (str[0] == NULL)
		return ;
	while (list[i] != NULL)
		check_str_helper(list, str, &i, expanded);
}

static size_t	get_len_dptr(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	**copy_to_new(char **str, char **appending, size_t *i, size_t b_len)
{
	char	**ret;
	size_t	a_len;
	size_t	j;

	a_len = get_len_dptr(appending);
	ret = ft_calloc(b_len + a_len, sizeof(char *));
	j = 0;
	while (j < *i)
	{
		ret[j] = ft_strdup(str[j]);
		j++;
	}
	while (j - *i < a_len)
	{
		ret[j] = ft_strdup(appending[j - *i]);
		j++;
	}
	*i += 1;
	while (j < a_len + b_len - 1)
		ret[j++] = ft_strdup(str[(*i)++]);
	return (ret);
}

void	split_str_i(char ***str, size_t *i)
{
	size_t	before_len;
	char	**appending;
	char	**new;

	before_len = get_len_dptr(*str);
	appending = ft_split((*str)[*i], " \t\n");
	new = copy_to_new(*str, appending, i, before_len);
	free_c_dptr(str);
	*str = new;
	*i = get_len_dptr(appending);
	free_c_dptr(&appending);
}
