/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:46:27 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 21:48:36 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "terminal.h"
#include "utils.h"
#include "parser.h"
#include <signal.h>
#include <stdio.h>
#include <readline/history.h>

#include <sys/wait.h> // temp
//parser part
t_cmd_line	*parse(t_context *context, const char *str, int *result)
{
	int	pid;
	int	status;
	t_cmd_line *cml;

	// cml = make_cmd(str); // 일단 space 기준으로 뜯어서 token 만듦(각각이 문법이 맞는지는 체크 안 함)

	// if (!ft_strncmp("loop", str, 5))
	// {
	// }
	// else if (!ft_strncmp("read", str, 5))
	// {
	// }
	return (cml);
}
//

static int	readline_loop(t_context *context, t_term_state *term_state)
{
	char		*str;
	t_cmd_line	*cml;
	t_error		*result;

	while (1)
	{
		str = ft_readline(term_state);
		if (!str)
			return (exit_with_status(END_TERM));
		if (*str)
			add_history(str);

		//  // 새롭게 정리한 토큰화부분
		char **s;
		t_token *a;
		a = convert_dptr_to_struct(tokenizer(str));
		s = convert_token_to_dptr(a);
		//테스트
		// int i = 0;
		// while (*(s + i) != NULL)
		// {
		// 	printf("|%s|\n", *(s + i));
		// 	i++;
		// }
		// cml = parse(context, s, result);

		// expand_tokens(context, str, envp); // 기존 구현부 연결
		
		cml = token_to_cmd_line(s);
		// 파싱 함수는
		// 구조체 리턴, context->result에 에러 여부 기록하여 리턴해야 함
		
		// context->exit_status = parse(str);
		// if (cml != NULL) // 파싱 성공시 채운 cml 리턴
		// 	*result = SUCCESS;
		// else // 파싱 실패시 null 리턴
		// 	*result = SYNTAX_ERROR;

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
	readline_loop(&context, &term_state); // 임시방편
	clear_envp_list(&(context.envp));
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (context.exit_status);
}
