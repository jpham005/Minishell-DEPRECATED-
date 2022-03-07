/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:52:59 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/07 15:55:03 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int	get_start(const char *line, t_tokenizer *tool)
{
	int	i;

	i = tool->idx;
	if (!line || !line[i] || tool->quote || tool->par)
		return (0);
	if ((tool->quote = get_quote(line, i)))
		tool->qidx = i;
	if (line[i] == '(')
	{
		tool->par++;
		tool->pidx = i;
		if (tool->par == 1)
			return (1);
	}
	if (ft_is_set(line[i], "><|&"))
	{
		if (tool->prev == line[i])
			return (0);
		tool->prev = line[i];
		return (1);
	}
	tool->prev = 0;
	if (!i)
		return (1);
	if (ft_is_space(line[i]))
		return (!ft_is_space(line[i - 1]));
	return (ft_is_space(line[i - 1]) || (ft_is_set(line[i - 1], "><|&")) || (i && line[i - 1] == ')' && !tool->par));
}

int	get_end(const char *line, t_tokenizer *tool)
{
	int	i;

	i = tool->idx;
	if (!line || tool->start == -1) 
		return (0);
	if (line[i] == tool->quote && tool->qidx != i)
		tool->quote = 0;
	if (tool->quote && (line[i + 1] == '\0'))
		return (1);
	if (tool->quote)
		return (0);
	if (line[i] == '(' && tool->pidx != i)
		tool->par++;
	if (line[i] == ')')
	{
		tool->par--;
		tool->pidx = i;
		if (tool->par == 0)
		{
			tool->pidx = 0;
			return (1);
		}
	}
	if (tool->par)
		return (0);
	if (!tool->par && line[i + 1] == '(')
		return (1);
	if (!line[i + 1] || (!tool->quote && line[i] == '\0'))
		return (1);
	if (!tool->quote && line[i + 1] == '\0')
		return (1);
	if (ft_is_space(line[i]))
		return (!(ft_is_space(line[i + 1])));
	if (ft_is_space(line[i + 1]))
		return (1);
	if (ft_is_set(line[i], "><|&"))
	{
		if ((line[i] != line[i + 1]) || ((tool->prev == line[i] && tool->start != i)))
			return (1);
		else
			return (0);
	}
	return (ft_is_set(line[i + 1], "><|&"));
}
