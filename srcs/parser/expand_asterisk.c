/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:14:26 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 18:03:00 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>

void	check_side(char **list, char *arg, int *arr)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (list[++i] != NULL)
	{
		if (
			((arg[0] == '*') || ((arg[0] != '*') && (list[i][0] == arg[0])))
			&& ((arg[ft_strlen(arg) - 1] == '*') \
			|| ((arg[ft_strlen(arg) - 1] != '*') \
			&& (list[i][ft_strlen(list[i]) - 1] == arg[ft_strlen(arg) - 1])))
			)
		{
			*(arr + j) = i;
			j++;
		}
	}
}

char	*expand_asterisk_helper(int arr[256], char **list)
{
	char	*tmp;
	char	*tmp2;
	size_t	cnt;
	size_t	k;

	cnt = 0;
	k = -1;
	tmp2 = NULL;
	while (arr[++k] != -1)
	{
		if (arr[k] > -1)
		{
			tmp = ft_strjoin(list[arr[k]], " ");
			tmp2 = ft_strjoin(tmp2, tmp);
			cnt++;
		}
	}
	if (cnt)
	{
		safe_free((void **) tmp);
		return (tmp2);
	}
	return (NULL);
}

char	*expand_asterisk(char *arg)
{
	char	**str; // asterlisk로 나눈 문자열(list에 있나 체크해야됨)
	char	**list;
	int		arr[256]; // list의 idx만 저장한 배열, 실제로는 파일/폴더가 256개 넘을 수 있으므로 나중에 수정해야됨
	char	*new;

	ft_memset(arr, -1, sizeof(int) * 256); // 이것도 -1 초기화 안 돼서 그냥 넣은 임시 초기화 코드
	str = ft_split(arg, '*');
	list = current_path_ls();
	check_side(list, arg, arr); // 양 끝이 조건 충족하는지 검사
	// // arg 체크 코드
	// printf ("===========sddasd============\n");
	// k = 0;
	// while(arr[k] != -1)
	//     printf("%d\n", arr[k++]);
	// printf ("===========asfasdf============\n");

	check_str(list, str, arr); // 사이에 str 있는지 검사
	// printf ("===========last============\n");
	new = expand_asterisk_helper(arr, list);
	if (new)
	{
		free(arg);
		arg = new;
	}
	return (arg);
	// printf ("===========last============\n");

	// // * 기준 split 상태 확인 코드
	// i = 0;
	// printf ("===========* split============\n");
	// while (*(str + i) != NULL)
	// 	printf("%s\n", str[i++]);
	// printf ("===========* split============\n");

	// 현재 폴더 내 자료 출력 확인 코드
	// i = 0;
	// printf ("===========current path file&directory============\n");
	// while (*(list + i) != NULL)
	// 	printf("%s\n", list[i++]);
	// printf ("===========current path file&directory============\n");

	// *: 현재 디렉토리의 모든 파일/폴더(ls 출력 결과를 char **all에 담기)
	// a*b*c: 별도 함수로 파싱. a, *, b ,*, c이런 식으로
	// 함수 하나 만들어서 인자로 들어온 **all에 들어있는 놈 하나랑 비교
	// cmp와 비슷한데 *나오면 *아닌 문자 나올때까지 skip 끝까지 갔는데 똑같으면 1리턴, 아니면 0리턴
	// 같은 놈만 살려놓고 틀린 놈은 날려버리기
	// **all에는 멀쩡한 것만 남을 것이고 만약에 all이 null이면 그냥 문자열로 생각하고 출력한다
}
