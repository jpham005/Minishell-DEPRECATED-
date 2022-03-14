/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 02:50:13 by jaham             #+#    #+#             */
/*   Updated: 2022/03/14 04:17:42 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static int	find_env_var(char *str, int start, t_context *context)
{
	char	*ret;
	int		len;
	int		temp;
	int		i;

	temp = start;
	len = 0;
	i = 0;
	while (is_env_var(str[temp++]))
		len++;
	ret = ft_calloc(sizeof(char), len + 1);
	while (len--)
		ret[i++] = str[start++];
	if (!find_list_by_key(context->envp, ret))
	{
		safe_free((void **) &ret);
		return (-1);
	}
	safe_free((void **) &ret);
	return (1);
}

static int	is_valid_dollar(char *str, int end, t_context *context)
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
	return (find_env_var(str, end + 1, context));
}

void	check_dollar(int *dollar_flag, char *str, t_context *context)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			dollar_flag[j++] = is_valid_dollar(str, i, context);
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
