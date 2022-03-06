/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 07:33:58 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/07 04:24:29 by jaham            ###   ########.fr       */
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

int	ft_is_space(int c)
{
	if (c == '\t' || c == '\r' || \
	c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

static void	token_init(t_tokenizer *tool)
{
	tool->idx = 0;
	tool->qidx = 0;
	tool->start = -1;
	tool->prev = 0;
	tool->par = 0;
	tool->pidx = 0;
	tool->quote = 0;
}

char	get_quote(const	char *line, int idx)
{
	char	quote;

	quote = 0;
	if (line[idx] == '\'')
		quote = '\'';
	else if (line[idx] == '\"')
		quote = '\"';
	return (quote);
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

char	**tokenizer(const char *line)
{
	t_tokenizer	tool;
	char		*token;
	char		**tokens;

	tokens = 0;
	token_init(&tool);
	while (line[tool.idx])
	{
		token = 0;
		if (get_start(line, &tool))
			tool.start = tool.idx;
		if (get_end(line, &tool))
		{
			token = ft_substr(line, tool.start, tool.idx - tool.start + 1);
			ft_realloc_doublestr(&tokens, token);
			ft_free_str(&token);
			tool.start = -1;
			tool.prev = 0;
		}
		tool.idx++;
	}
	if (tool.par != 0)
		return (NULL);
	return (tokens);
}
