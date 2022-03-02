/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:14:26 by jaham             #+#    #+#             */
/*   Updated: 2022/03/02 14:30:04 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>

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
	printf("%s\n", no_q);
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
