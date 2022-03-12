/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:37:13 by jaham             #+#    #+#             */
/*   Updated: 2022/03/12 17:48:14 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static void	init_change_dollar(char **temp_s, t_index *idx)
{
	*temp_s = NULL;
	ft_memset(idx, 0, sizeof(t_index));
}

static void	increase_idx(t_index *idx)
{
	idx->i += 1;
	idx->j += 1;
}

void	change_dollar(t_context *ctx, int *dollar_flag, char *str, char **new)
{
	char	*temp_s;
	char	*expand_value;
	t_index	idx;

	init_change_dollar(&temp_s, &idx);
	while (str[idx.i])
	{
		if (str[idx.i] == '$' && str[idx.i + 1] == '?' && dollar_flag[idx.j])
		{
			expand_estat(&expand_value, new, &temp_s, ctx);
			increase_idx(&idx);
		}
		else if (dollar_flag[idx.j] == -1)
			return ;
		else if (is_no_expand(str, &idx, dollar_flag))
			ft_charjoin(new, &temp_s, str[idx.i]);
		else
		{
			get_expand_val(&idx.i, str, ctx, &expand_value);
			get_new(&expand_value, new, &temp_s, &idx.i);
		}
		idx.i++;
	}
	if (*new == NULL)
		*new = ft_strdup("");
}

static int	remake_str(char ***str, int *i, int **dollar_flag)
{
	char	**new_str;
	size_t	size;
	int		j;
	int		k;

	size = 0;
	while ((*str)[size])
		size++;
	new_str = ft_malloc(sizeof(char *), size);
	j = 0;
	k = 0;
	while ((*str)[j])
	{
		if (*i != j)
			new_str[k++] = ft_strdup((*str)[j]);
		j++;
	}
	new_str[k] = NULL;
	free_c_dptr(str);
	*str = new_str;
	*i -= 1;
	safe_free((void **) dollar_flag);
	return (1);
}

void	expand_dollars(t_context *context, char ***str)
{
	int		i;
	int		cnt;
	int		*dollar_flag;
	char	*new;

	i = -1;
	cnt = 0;
	dollar_flag = NULL;
	while ((*str)[++i])
	{
		new = NULL;
		cnt = count_dollar((*str)[i]);
		if (cnt == 0)
			continue ;
		dollar_flag = ft_calloc(sizeof(int), cnt + 1);
		dollar_flag[cnt] = -2;
		check_dollar(dollar_flag, (*str)[i], context);
		change_dollar(context, dollar_flag, (*str)[i], &new);
		if (!new && remake_str(str, &i, &dollar_flag))
			continue ;
		safe_free((void **) &((*str)[i]));
		(*str)[i] = new;
		safe_free((void **) &dollar_flag);
	}
}
