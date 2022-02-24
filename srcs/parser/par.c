/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:23:31 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/02/25 00:05:21 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>

void    del_q(char *str, char c)
{
	int i = 0;
	while (str[i] != '\0')
	{
		str[i] = str[i + 1];
		i++;
	}
}

char    **find_path(char *str, char **envp)
{
	char **path;
	char **cmd_str;
	char *tmp;
	char *cmd_path;
	int i;
	
	/* path_list */
	i = 0;
	while (*(envp + i) != NULL)
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' &&
		envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
		{
			path = ft_split(&envp[i][5], ':');
			break;
		}
		i++;
	}

	/* split str (readline) */
	cmd_str = ft_split(str, ' ');

	// [/usr/bin + / + cmd]
	i = 0;
	while (*(path + i) != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(tmp, cmd_str[0]);
		if (access(cmd_path, X_OK) == 0)
			break;
		i++;
	}
	safe_free((void **) &tmp);
	tmp = cmd_str[0];
	cmd_str[0] = cmd_path;
	safe_free((void **) &tmp);
	return (cmd_str); // /ooo/ooo/cmd
}

// asterisk start
int is_asterisk(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

// ., ..을 제외한 현재 경로의 파일, 폴더 리스트 리턴
// .으로 시작하는 파일, 폴더는 스킵하도록 수정해야 함
char **current_path_ls(void)
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

char **check_side(char **list, char *arg, int *arr)
{;
	int i;
	int j;

	i = -1;
	j = 0;
	while (list[++i] != NULL)
	{
		if (
			((arg[0] == '*') || ((arg[0] != '*') && (list[i][0] == arg[0])))
			&& ((arg[ft_strlen(arg) - 1] == '*') || ((arg[ft_strlen(arg) - 1] != '*') && (list[i][ft_strlen(list[i]) - 1] == arg[ft_strlen(arg) - 1])))
			)
		{
			*(arr + j) = i;
			j++;
		}
	}
}

void	check_str(char **list, char **str, int *arr)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	if (str[j] == NULL)
		return ;
	while (arr[i] != -1)
	{
		j = 0;
		tmp = list[arr[i]];
		while (1)
		{
			tmp = ft_strnstr(tmp, str[j], ft_strlen(tmp));
			if (tmp != NULL)
			{
				if (str[j + 1] != NULL)
					j++;
				else
				{
					i++;
					break;
				}
			}
			else
			{
				*(arr + i) = -2;
				i++;
				break;
			}
		}
	}
}

char *expand_asterisk(char *arg)
{
	int cnt;
	char **str; // asterlisk로 나눈 문자열(list에 있나 체크해야됨)
	char **list;
	int arr[256]; // list의 idx만 저장한 배열, 실제로는 파일/폴더가 256개 넘을 수 있으므로 나중에 수정해야됨
	int i;
	int k;

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
	k = -1;
	char *tmp;
	char *tmp2 = NULL;
	cnt = 0;
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
		arg = tmp2;
	return arg;
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
char **par4(char **pars_str, char **envp, char *env_val, int ss_idx)
{
	int i;
	int j;
	int len;
	char *list_key = "SHELL"; // env들 구조체로 바꿔야됨
	char *value;
	char *ex_str;

	value = NULL;
	ex_str = NULL;
	if (ft_strcmp(list_key, env_val) == 0)
		value = ft_strdup("/bin/bash"); // strdup() == list_value
	// "$SHELL-123" --> /bin/bash-123
	len = ft_strlen(pars_str[ss_idx]) - (1 + ft_strlen(env_val)) + ft_strlen(value);
	ex_str = ft_malloc(sizeof(char), len + 1);
	i = -1;
	j = 0;
	if (ss_idx != 0)
	{
		while (pars_str[ss_idx][++i] != '$')
			ex_str[i] = pars_str[ss_idx][i];
		if (value != NULL)
		{
			int idx = i + ft_strlen(env_val);
			while (value[j] != '\0')
				ex_str[i++] = value[j++];
			while (pars_str[ss_idx][++idx] != '\0')
				ex_str[i++] = pars_str[ss_idx][idx];
		}
		ex_str[i] = '\0';
		printf("ex-str :: %s\n", ex_str);
		safe_free((void **) &pars_str[ss_idx]);
		pars_str[ss_idx] = ex_str;
	}

	i = 0;
	while (*(pars_str + i) != NULL)
	{
		printf("%s\n", *(pars_str + i));
		i++;
	}
	return (pars_str);
}

/* env 환경변수명 찾는 부분 " 포함해야 함 */
char **par3(char **pars_str, char **envp, int flag_q)
{
	int i;
	int j;
	int k;
	char *env_val;
	int ss_idx;
	int s_idx;

	i = 0;
	env_val = NULL;
	ss_idx = 0;
	if (flag_q != 1)
	{
		while (pars_str[i] != NULL)
		{
			j = 0;
			while (pars_str[i][j] != '\0')
			{
				if (pars_str[i][j] == '$')
				{
					ss_idx = i;
					s_idx = j + 1;
					k = 1;
					while (pars_str[i][j + k] == '_' || ft_isdigit(pars_str[i][j + k]) || ft_isalpha(pars_str[i][j + k]))
						k++;
					env_val = ft_malloc(sizeof(char), k);
					ft_strlcpy(env_val, &pars_str[i][j + 1], k);
				}
				j++;
			}
			i++;
		}
	} // return (env_val);
	printf("env_val :: %s\n", env_val);

	/* env_list key:value */
	/* env_list cmp(env_val == list_key) : list_value ? loop */
	/*  */

	return (par4(pars_str, envp, env_val, ss_idx));
}

char **par2(char **pars_str, char **envp)
{
	int i;
	int flag_q;
	int flag_qq;

	i = 0;
	flag_q = 0;
	flag_qq = 0;

	/* del q */
	while (*(pars_str + i) != NULL)
	{
		if (pars_str[i][0] == '\'')
		{
			del_q(pars_str[i], '\''); // 'err\0 --> err\0\0 || err'\0 --> err\0\0
			flag_q = 1;
		}
		else if (pars_str[i][0] == '\"')
		{
			del_q(pars_str[i], '\"');
			flag_qq = 1;
		}
		if (pars_str[i + 1] == NULL && (flag_q || flag_qq))
		{
			int j = 0;
			while (pars_str[i][j] != '\0')
			{
				if (pars_str[i][j + 1] == '\0')
					pars_str[i][j] = '\0';
				j++;
			}
		}
		i++;
	}
	return (par3(pars_str, envp, flag_q));
}

char **par(char *str, char **envp)
{
	char **pars_str = find_path(str, envp);
	int i;

	// asterisk expand
	i = 0;
	while (*(pars_str + i) != NULL)
	{
		if (is_asterisk(pars_str[i]))
		{
			*(pars_str + i) = expand_asterisk(*(pars_str + i));
			break;
		}
		i++;
	}
	return (par2(pars_str, envp));
}

void    ft_exec(char **rtc)
{
	// fork()
	printf("\n================\n");
	execve(rtc[0], rtc, NULL); // 프로세스 CMD로 넘어가므로 일반적으로 하단은 실행 안 됨
	printf("\n================\n"); // 하단
}

void	parse_main(char *str, char **envp)
{
	char **readline_to_cmd;
	
	readline_to_cmd = par(str, envp);
	ft_exec(readline_to_cmd);
}

// 처음에 파이프 개수만 세서 cl->pipes->num에 저장한 다음 그 크기 - 1만큼 next를 붙인 구조체 완성
// next가 null일 때까지 type과 cmds->cmd를 채운다는 느낌으로 작성해야 함
// 각각의 cmds->cmd는 par()를 통해 명령어와 환경 변수 등이 확장 처리됨
// void	check_pipe(char **str, t_cmd_line *cl)
// {
// 	char **temp;
// 	int i;

// 	i = 0;
// 	temp = str; // ft_strdup 2차원 고려하여 복사
// 	while (*(str + i) != NULL)
// 	{
// 		if (str[0][0] == '|' && str[0][1] == '|' && str[0][2] == '\0')
// 			cl->pipes->type = OR;
// 		else if (str[0][0] == '|' && str[0][1] == '\0')
// 			cl->pipes->type = PIPE;
// 		else if (str[0][0] == '&' && str[0][1] == '&' && str[0][2] == '\0')
// 			cl->pipes->type = AND;
// 		// cl->pipes->cmds->cmd = 이전 파이프 다음 인덱스부터 현재 파이프 이전 인덱스까지
// 		i++;
// 	}
// 	// num++, s_cmd_line 쪼개기
// }

