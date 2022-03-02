/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:23:31 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/02 15:33:06 by hyeonpar         ###   ########.fr       */
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
		{
			printf("bef: %s\n", str[i]);
			str[i] = expand_asterisk(str[i]); // *가 포함된 문자열을 확장
			printf("aft: %s\n", str[i]);
		}
		i++;
	}
}

void	delete_quote_2(char **str, int len, int i)
{
	char *s;
	int	j;
	char quote;

	s = ft_malloc(sizeof(char), len + 1);
	j = 0;
	quote = 0;
	len = 0;
	while (str[i][j])
	{
		if (quote == 0 && (str[i][j] == '\'' || str[i][j] == '\"'))
		{
			quote = str[i][j];
		}
		else if ((quote == '\'' && str[i][j] == '\'') || (quote == '\"' && str[i][j] == '\"'))
			quote = 0;
		s[j] = str[i][j];
		j++;
	}
	// i = -1;
	// len = 0;
	// while (arg[++i] != '\0')
	// {
	// 	if (arg[i] =='\'' || arg[i] =='\"')
	// 		continue;
	// 	no_q[len] = arg[i];
	// 	printf("len: %d\n", len);
	// 	len++;
	// }
	// no_q[len] = '\0';
	// return (no_q);
}

void	delete_quote_1(char **str)
{
	int i;
	int	j;
	int	quote;
	int	len;

	i = 0;
	while (str[i])
	{
		j = 0;
		quote = 0;
		len = 0;
		while(str[i][j])
		{
			if (quote == 0 && (str[i][j] == '\'' || str[i][j] == '\"'))
				quote = str[i][j];
			else if ((quote == '\'' && str[i][j] == '\'') || (quote == '\"' && str[i][j] == '\"'))
				quote = 0;
			len++;
			j++;
		}
		delete_quote_2(str, len, i);
		i++;
	}
}

void	expand_tokens(t_context *context, char **str)
{
	par(context, str); // 아스터리스크 확장하고
	// delete_quote(str);
}