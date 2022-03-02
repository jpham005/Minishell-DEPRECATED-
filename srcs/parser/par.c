/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:23:31 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/03 03:13:24 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "terminal.h"
#include <stdio.h>

// s가 str 안에 있으면 인덱스, 아니면 -1 리턴
int	find_char(char *str, char s)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == s)
			return (i);
		i++;
	}
	return (-1);
}

// asterisk start
int	is_asterisk(char *str)
{
	int i;
	int j;
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
		else if ((quote == '\'' && str[i] == '\'') || (quote == '\"' && str[i] == '\"'))
			quote = 0;
		i++;
	}
	if (quote)
		return (0);
	return (1);
}

// ., ..을 제외한 현재 경로의 파일, 폴더 리스트 리턴
// .으로 시작하는 파일, 폴더는 스킵하도록 수정해야 함
char	**current_path_ls(void)
{
	DIR *dp;
	struct dirent *dirp;
	int i;
	char *arr[256];
	char **res;

	dp = opendir(".");
	i = 0;
	while (1)
	{
		dirp = readdir(dp);
		if (dirp == NULL)
			break;
		if (dirp->d_name[0] != '.')
			arr[i++] = ft_strdup(dirp->d_name);
	}
	res = (char **)ft_calloc(sizeof(char *), i + 1);
	*(res + i) = NULL;
	while (--i > -1)
		*(res + i) = arr[i];
	closedir(dp);
	return (res);
}

void	par(t_context *context, char **str) // str의 유효한 아스터리스크 문자열을 확장해주는 함수
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_asterisk(str[i]))
			str[i] = expand_asterisk(str[i]); // *가 포함된 문자열을 확장
		i++;
	}
}

void	delete_quote_2(char **str, int len, int i)
{
	char *s;
	int	j;
	char quote;

	s = ft_malloc(sizeof(char), len + 1);
	j = -1;
	quote = 0;
	len = 0;
	while(str[i][++j])
	{
		if (quote == 0 && (str[i][j] == '\'' || str[i][j] == '\"'))
		{
			quote = str[i][j];
			continue;
		}
		else if ((quote == '\'' && str[i][j] == '\'') || (quote == '\"' && str[i][j] == '\"'))
		{
			quote = 0;
			continue;
		}
		s[len++] = str[i][j];
	}
	s[len] = '\0';
	safe_free((void **) &str[i]);
	str[i] = ft_strdup(s);
	safe_free((void **) &s);
}

void	delete_quote_1(char **str)
{
	int i;
	int	j;
	int	quote;
	int	len;

	i = -1;
	while (str[++i])
	{
		j = -1;
		quote = 0;
		len = 0;
		while(str[i][++j])
		{
			if (quote == 0 && (str[i][j] == '\'' || str[i][j] == '\"'))
			{
				quote = str[i][j];
				continue;
			}
			else if ((quote == '\'' && str[i][j] == '\'') || (quote == '\"' && str[i][j] == '\"'))
			{
				quote = 0;
				continue;
			}
			len++;
		}
		delete_quote_2(str, len, i);
		// if quote = 1이면 
		// 2 함수로 안 가고 에러처리(실제 bash에서는 추가적인 입력을 대기하지만 일단 여기서는 끝 콤마가 열려있는 상태면 에러 처리함)
	}
}

void	expand_tokens(t_context *context, char **str)
{
	par(context, str); // 아스터리스크 확장하고
	delete_quote_1(str); // 지금까지 남아있던 따옴표 전부 제거
}