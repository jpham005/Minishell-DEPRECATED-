/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:23:31 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/02/27 20:34:42 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "terminal.h"
#include <stdio.h>

// asterisk start
int	is_asterisk(char *str)
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

char	**par(char *str, t_context *context)
{
	char	**pars_str;
	size_t	i;

	// asterisk expand
	pars_str = ft_split(str, ' ');
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
	return (par2(pars_str, context));
}

void	ft_exec(char **rtc)
{
	// fork()
	printf("\n================\n");
	execve(rtc[0], rtc, NULL); // 프로세스 CMD로 넘어가므로 일반적으로 하단은 실행 안 됨
	printf("\n================\n"); // 하단
}

void	expand_tokens(char *str, t_context *context)
{
	char	**readline_to_cmd;

	readline_to_cmd = par(str, context);
	ft_exec(readline_to_cmd);
}