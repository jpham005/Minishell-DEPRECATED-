#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>

extern char	**ft_split(char const *s, char c);
extern size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int ft_strlen(char *s);

typedef struct s_env
{
	char **env_path;
}   t_env;

char *ft_strjoin(char *s1, char *s2)
{
	char *str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	int i = 0;

	if (s1 == NULL)
		return s2;
	if (s2 == NULL)
		return s1;

	while (*s1 != NULL)
	{
		str[i++] = *s1++;
	}
	while (*s2 != NULL)
	{
		str[i++] = *s2++;
	}
	str[i] = '\0';
	return (str);
}

int ft_strcmp(char *s1, char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (1);
	return (strcmp(s1, s2));
}

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
	// char *p = "PATH=";
	char **path;
	int i;
	
	/* path_list */
	i = 0;
	while (*(envp + i) != NULL)
	{
		// printf("%s\n", *(envp + i));
		if (envp[i][0] == 'P' && envp[i][1] == 'A' &&
		envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
		{
			path = ft_split(&envp[i][5], ':');
			break;
		}
		i++;
	}

	/* split str (readline) */
	char **cmd_str = ft_split(str, ' ');

	// [/usr/bin + / + cmd]
	i = 0;
	char *tmp;
	char *cmd_path;
	while (*(path + i) != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(tmp, cmd_str[0]);
		if (access(cmd_path, X_OK) == 0)
			break;
		i++;
	}
	free(tmp);
	tmp = cmd_str[0];
	cmd_str[0] = cmd_path;
	free(tmp);
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
		if ((dirp != NULL))
			arr[i] = strdup(dirp->d_name);
		else
			break;
		i++;
	}
	res = (char **)calloc(sizeof(char *), i);
	while (i > 1)
	{
		*(res + i - 2) = arr[i];
		i--;
	}
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
			// printf("tmp now: %s\n", tmp);
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

	memset(arr, -1, sizeof(int) * 256); // 이것도 -1 초기화 안 돼서 그냥 넣은 임시 초기화 코드
	
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
	// char *tmp2 = "";
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

char **par(char *str, char **envp)
{
	// check str, check_readline(); == false
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

	i = 0;
	while (*(pars_str + i) != NULL)
	{
		printf("%s\n", *(pars_str + i));
		i++;
	}

	printf("==========================\n");
	// char *echo[] = {"/bin/ls", "err", "*", NULL};
	// char **cmd[] = {echo, NULL};
	// execve("/bin/ls", cmd[0], envp);
	// execve(pars_str[0], pars_str, envp);

	/* del q */
	i = 0;
	int flag_q = 0;
	int flag_qq = 0;

	while (*(pars_str + i) != NULL)
	{
		if (pars_str[i][0] == '\'')
		{
			del_q(pars_str[i], '\''); // 'err\0 --> err\0\0     ||      err'\0 --> err\0\0
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

	/* env 환경변수명 찾는 부분 " 포함해야 함 */
	i = 0;
	char *env_val = NULL;
	int ss_idx = 0;
	if (flag_q != 1)
	{
		while (pars_str[i] != NULL)
		{
			int j = 0;
			while (pars_str[i][j] != '\0')
			{
				if (pars_str[i][j] == '$')
				{
					ss_idx = i;
					int s_idx = j + 1;
					int k = 1;
					while (pars_str[i][j + k] == '_' || isdigit(pars_str[i][j + k]) || isalpha(pars_str[i][j + k]))
					{
						k++;
					}
					env_val = (char *)malloc(k);
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
	char *list_key = "SHELL";
	char *value = NULL;
	if (ft_strcmp(list_key, env_val) == 0)
		value = strdup("/bin/bash"); // strdup() == list_value
	char *ex_str = NULL;

	// "$SHELL-123" --> /bin/bash-123
	int len = ft_strlen(pars_str[ss_idx]) - ft_strlen(env_val) + 1 + ft_strlen(value);
	ex_str = (char *)malloc(len + 1);
	i = -1;
	int j = 0;
	if (ss_idx != 0)
	{
		while (pars_str[ss_idx][++i] != '$')
			ex_str[i] = pars_str[ss_idx][i];
		if (value != NULL)
		{
			int idx = i + strlen(env_val);
			while (value[j] != '\0')
				ex_str[i++] = value[j++];
			while (pars_str[ss_idx][++idx] != '\0')
				ex_str[i++] = pars_str[ss_idx][idx];
			printf("ex-str :: %s\n", ex_str);
		}
		ex_str[i] = '\0';
		free(pars_str[ss_idx]);
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

void    ft_exec(char **rtc)
{
	// fork()
	printf("\n================\n");
	execve(rtc[0], rtc, NULL); // 프로세스 CMD로 넘어가므로 일반적으로 하단은 실행 안 됨
	printf("\n================\n"); // 하단
}

int main(int argc, char *argv[], char *envp[])
{
	// char *str = strdup("echo -n $SHELL"); // << readline 입력한 문자열
	// char *str = strdup("echo $SHELL"); // << readline 입력한 문자열
	char *str = strdup("echo -n *"); // << readline 입력한 문자열

	// check str, check_readline(); == false
	char **readline_to_cmd = par(str, envp);
	ft_exec(readline_to_cmd);
	
	free(str);
	return (0);
}