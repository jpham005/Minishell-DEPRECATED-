/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 07:33:58 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/02/27 13:07:29 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// &&는 두 개 연속으로만 끊어주고, space 처리

#include "libft.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h> // free 때문에 잠깐 썼음

int		ft_free_str(char **str) // 바꿔야됨
{
	if (!str || !(*str))
		return (0);
	free(*str);
	*str = '\0';
	return (1);
}

int		ft_free_doublestr(char ***doublestr_addr)
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

int		ft_len_doublestr(char **str)
{
	int		idx;

	idx = 0;
	if (!str || !(*str))
		return (0);
	while (*str++)
		idx++;
	return (idx);
}

char	**ft_realloc_doublestr(char ***strs_ref, char *item)
{
	char	**ret;
	char	**strs;
	int		len;

	strs = *strs_ref;
	if (!item)
		return (strs);
	len = ft_len_doublestr(strs) + 2;
	if (!(ret = (char **)ft_calloc(sizeof(char *), len--)))
		return (0);
	ret[--len] = ft_strdup(item);
	while (len--)
		if (!(ret[len] = ft_strdup(strs[len])))
			return (0);
	*strs_ref = ret;
	ft_free_doublestr(&strs);
	return (ret);
}

int		ft_is_set(char c, char *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int		ft_is_space(int c) // 이름 수정
{
	if (c == '\t' || c == '\r' || \
	c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

// 위로는 libft로 넘기자

static void		token_init(t_tokenizer *tool)
{
	tool->idx = 0;
	tool->qidx = 0;
	tool->start = -1;
	tool->prev = 0;
	tool->quote = 0;
}

char			get_quote(char *line, int idx)
{
	char	quote;

	quote = 0;
	if (line[idx] == '\'')
		quote = '\'';
	else if (line[idx] == '\"')
		quote = '\"';
	return (quote);
}

int				get_end(char *line, t_tokenizer *tool)
{
	int		i;

	i = tool->idx;
	if (!line || tool->start == -1)
		return (0);
	if (line[i] == tool->quote && tool->qidx != i) // 현재 코트이고 코트 인덱스가 아니라면
		tool->quote = 0;
	if (!line[i + 1] || (!tool->quote && line[i] == '\0'))
		return (1);
	if (!tool->quote && line[i + 1] == '\0')
		return (1);
	if (tool->quote)
		return (0);
	if (ft_is_space(line[i]))
		return (!(ft_is_space(line[i + 1])));
	if (ft_is_space(line[i + 1]))
		return (1);
	if (ft_is_set(line[i], "><|&"))
	{
		if (line[i] != line[i + 1])
			return (1);
		return ((tool->prev == line[i] && tool->start != i) ? 1 : 0);
	}
	return (ft_is_set(line[i + 1], "><|&") ? 1 : 0);
}

int				get_start(char *line, t_tokenizer *tool)
{
	int		i;

	i = tool->idx; // 현재 인덱스
	if (!line || !line[i] || tool->quote) // ', " 있거나 널문자, 라인이 널이면 시작 아님
		return (0);
	if ((tool->quote = get_quote(line, i))) // 현재 인덱스가 ', "이면(코트 문자 값 그대로 넣음)
		tool->qidx = i; // 코트 인덱스 시작점(qidx) 갱신
	// if (line[i] == '\n')
	// 	return (TRUE);
	if (ft_is_set(line[i], "><|&")) // 파이프나 <, >이면
	{
		if (tool->prev == line[i]) // 이전에도 있었으면 안됨
			return (0);
		tool->prev = line[i]; // 이전에 없었으면 이전 갱신하고 트루 리턴
		return (1);
	}
	tool->prev = 0;
	if (!tool->idx) // 0인덱스, 함수 처음이면
		return (1);
	if (ft_is_space(line[i])) // space면
		return (!ft_is_space(line[i - 1])); // 이전도 스페이스인 것이 아니면 1리턴
	return (ft_is_space(line[i - 1]) || (ft_is_set(line[i - 1], "><|&"))); // 이전 스페이스 아니거나 이전이 리디렉션 아니면 true이다
}

// 위는 다 이 함수를 위한 것이라 static 처리하면 됨
char			**tokenizer(char *line)
{
	t_tokenizer		tool;
	char			*token;
	char			**tokens;

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

	//테스트
	// int i = 0;
	// while (*(tokens + i) != NULL)
	// {
	// 	printf("#%s#\n", *(tokens + i));
	// 	i++;
	// }
	
	return (tokens);
}