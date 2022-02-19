/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:46:27 by jaham             #+#    #+#             */
/*   Updated: 2022/02/20 05:18:52 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "terminal.h"
#include "utils.h"
#include <signal.h>
#include <stdio.h>
#include <readline/history.h>

#include <sys/wait.h> // temp
//parser part
static int	parse(const char *str)
{
	// exit status 리턴
	
	// 사전 준비(pipex와 크게 다르지 않음, 추가된 느낌)
	// envp 구조체에는 등록된 환경 변수가 key value로 들어가있음

	// envp**에서 PATH로 시작하는 envp[i] 찾고
	// PATH= 이후 문자열 path split 함수로 : 기준으로 자르기
	// access함수를 통해 path + / + cmd가 되는지 돌려보고 되는 게 있으면 되는 cmd므로 합친 경로를 리턴, 안 되면 에러처리 번호를 리턴
	// cmd는 문자열의 0인덱스에 있을 것이다
	// echo -> /bin/echo 이런 식으로 치환되는 셈

	// 큰 따옴표, 작은 따옴표는 flag/enum으로 표시
	// 따옴표가 맨 앞에 있으면 flag 수치 바꾸고 왼쪽으로 밀고 마지막자리에 널 추가
	// 일단 이런 느낌

	// $ 다음 어디까지가 붙었을 때 허용되는가? -> 환경변수명은 알파벳 대소문자, 숫자, 언더바(_)만으로 이루어져 있으므로 이외는 환경변수명이 아니라고 처리하면 됨


	// 와일드카드 문자 사용
	// *가 붙어있는 토큰을 ls해서 나온 결과로 치환
	// 문자는 여러 개 나올 수 있음, ls 같은 명령어 요구 안 하므로 ls 결괏값을 포인터로 담아서 처리해야 할 것 같은데
	// 정확한 사항은 일단 하면서 생각해야 할 듯

	// $?
	// $ 처리할 때 추가해줘야 함

	// 

	// 입력 받고
	// 
	

	int	pid;
	int	status;

	if (!ft_strncmp("loop", str, 5))
	{
		pid = fork();
		if (!pid)
			execve("jaham_test/loop", NULL, NULL);
		else
			waitpid(pid, &status, 0);
	}
	else if (!ft_strncmp("read", str, 5))
	{
		pid = fork();
		if (!pid)
		{
			execve("jaham_test/read", NULL, NULL);
			write(1, "error\n", 6);
		}
		else
			waitpid(pid, &status, 0);
	}
	return (123);
}
//

static int	readline_loop(t_context *context, t_term_state *term_state)
{
	char	*str;

	while (1)
	{
		str = ft_readline(term_state);
		if (!str)
			return (exit_with_status(END_TERM));
		if (*str)
		{
			add_history(str);
			printf("input: %s\n", str); // str 확인
		}
		context->exit_status = parse(str);
		// 파싱 결과(구조체)를 실행부로 넘김
		safe_free((void **) &str);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_context		context;
	t_term_state	term_state;

	if (!check_arg(argc, (const char **) argv))
		exit_with_status(ARG_ERR);
	if (!check_tty(STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO))
		exit_with_status(DEFAULT_FD_ERR);
	init_shell(&context, &term_state, (const char **) envp);
	if (!print_intro())
		exit_with_status(PRINT_INTRO_ERR);
	readline_loop(&context, &term_state);
	clear_envp_list(&(context.envp));
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	while (1);
	return (context.exit_status);
}
