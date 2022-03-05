/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:23:31 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/05 15:19:35 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>

char	*expand_asterisk_helper(char **list)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = -1;
	tmp2 = NULL;
	while (list[++i] != NULL)
	{
		if (ft_strncmp(list[i], " ", 1) != 0)
		{
			tmp = ft_strjoin(list[i], " ");
			tmp2 = ft_strjoin(tmp2, tmp);
		}
	}
	// safe_free((void **) &tmp);
	return (tmp2);
}

void	check_str_helper(char **list, char **str, int *i)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = list[*i];
	while (1)
	{
		tmp = ft_strnstr(tmp, str[j], ft_strlen(tmp));
		if (tmp != NULL)
		{
			if (str[j + 1] != NULL)
				j++;
			else
			{
				(*i)++;
				break;
			}
		}
		else
		{
			safe_free((void **) &list[*i]);
			list[*i] = ft_strdup(" ");
			(*i)++;
			break;
		}
	}
}

void	check_str(char **list, char **str)
{
	int		i;

	i = 0;
	if (str[0] == NULL)
		return ;
	while (list[i] != NULL)
		check_str_helper(list, str, &i);
}

void	check_side(char **list, char *arg)
{
	int i;

	i = -1;
	while (list[++i] != NULL)
	{
		if (
			((arg[0] == '*') || ((arg[0] != '*') && (list[i][0] == arg[0])))
			&& ((arg[ft_strlen(arg) - 1] == '*') \
			|| ((arg[ft_strlen(arg) - 1] != '*') \
			&& (list[i][ft_strlen(list[i]) - 1] == arg[ft_strlen(arg) - 1])))
			)
			continue;
		else
		{
			safe_free((void **) &list[i]);
			list[i] = ft_strdup(" ");
		}
	}
}

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

char	*del_quote(char *arg)
{
	int i;
	int len;
	char quote;
	char *no_q;

	i = -1;
	len = 0;
	quote = 0;
	while (arg[++i] != '\0')
	{
		if (quote == 0 && (arg[i] =='\'' || arg[i] =='\"')) // quote 안이 아닌 상태에서 quote를 발견하면 추가하고 넘어감
		{
			quote = arg[i];
			continue;
		}
		else if (quote != 0 && quote == arg[i]) // quote 안에서 quote를 발견하면 quote 0 만들고 넘어감
		{
			quote = 0;
			continue;
		}
		len++; // 나머지 경우는 len++
	}
	no_q = ft_malloc(sizeof(char), len + 1);
	i = -1;
	len = 0;
	quote = 0;
	while (arg[++i] != '\0')
	{
		if (quote == 0 && (arg[i] =='\'' || arg[i] =='\"'))
		{
			quote = arg[i];
			continue;
		}
		else if (quote != 0 && quote == arg[i])
		{
			quote = 0;
			continue;
		}
		no_q[len] = arg[i];
		len++;
	}
	no_q[len] = '\0';
	return (no_q);
}

char	*expand_asterisk(char *arg) // arg는 아스터리스크가 확장될 수 있는(유효한) 문자열덩어리
{
	char	**str; // asterlisk로 나눈 문자열(list에 있나 체크해야됨)
	char	*no_q;
	char	**list;
	char	*new;

	no_q = del_quote(arg); // quote 빼고 문자열의 길이가 얼마나 되는지 구하고,길이만큼 새로운 문자열 말록하고, 거기에 코트 빼고 다 넣어
	list = current_path_ls();
	check_side(list, no_q); // 양 끝이 조건 충족하는지 검사, 충족 안 하면 스페이스만 넣어버림

	str = ft_split(no_q, '*');
	check_str(list, str); // 사이에 str 있는지 검사
	new = expand_asterisk_helper(list);
	if (new)
	{
		free(arg);
		arg = new;
	}
	safe_free((void **) str);
	safe_free((void **) list);

	return (arg);
}

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

void	expand_asterisks(t_context *context, char **str)
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