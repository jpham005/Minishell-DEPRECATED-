/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:37:13 by jaham             #+#    #+#             */
/*   Updated: 2022/03/07 16:04:37 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	change_dollar(t_context *ctx, int *dollar_flag, char *str, char **new)
{
	char	*temp_s;
	char	*expand_value;
	t_index	idx;

	temp_s = NULL;
	ft_memset(&idx, 0, sizeof(t_index));
	while (str[idx.i])
	{
		if (str[idx.i] == '$' && str[idx.i + 1] == '?' && dollar_flag[idx.j])
		{
			expand_estat(&expand_value, new, &temp_s, ctx);
			idx.i++;
			idx.j++;
		}
		else if (is_no_expand(str, idx.i, idx.j, dollar_flag))
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

void	expand_dollars(t_context *context, char **str)
{
	int		i;
	int		cnt;
	int		*dollar_flag;
	char	*new;

	i = -1;
	cnt = 0;
	dollar_flag = NULL;
	while (str[++i])
	{
		cnt = count_dollar(str[i]);
		if (cnt == 0)
			continue ;
		dollar_flag = ft_calloc(sizeof(int), cnt + 1);
		dollar_flag[cnt] = -2;
		check_dollar(dollar_flag, str[i]);
		change_dollar(context, dollar_flag, str[i], &new);
		safe_free((void **) &str[i]);
		str[i] = new;
		safe_free((void **) &dollar_flag);
	}
}
