/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 02:50:13 by jaham             #+#    #+#             */
/*   Updated: 2022/03/07 18:19:27 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static int	is_valid_dollar(char *str, int end)
{
	int	quote;
	int	i;

	i = 0;
	quote = 0;
	while (i <= end)
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (quote == 0)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		i++;
	}
	if (quote == '\'')
		return (0);
	return (1);
}

void	check_dollar(int *dollar_flag, char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			dollar_flag[j++] = is_valid_dollar(str, i);
	}
}

int	is_env_var(char c)
{
	if ((ft_isalpha(c) || ft_isdigit(c) || c == '_'))
		return (1);
	return (0);
}

int	count_dollar(char *s)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == '$')
			cnt++;
		i++;
	}
	return (cnt);
}
