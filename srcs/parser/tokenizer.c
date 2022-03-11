/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 07:33:58 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/07 15:54:51 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h> 

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
