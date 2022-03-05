/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:46:27 by jaham             #+#    #+#             */
/*   Updated: 2022/03/06 03:51:41 by jaham            ###   ########.fr       */
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

t_cmd_line	*parse(t_context *context, const char *str, int *result)
{
	t_cmd_line *cml;
	char **t;
	char **s;
	t_token *a;

	t = tokenizer(str);
	// int i = 0;
    // while (t[i])
    // {
    //     printf("%s\n", t[i++]);
    // }
	if (!t)
	{
		printf("괄호 열림\n");
		return (NULL);
	}
	a = convert_dptr_to_struct(t);
	s = convert_token_to_dptr(a);

	expand_dollars(context, s);
	expand_asterisks(context, s);

	cml = token_to_cmd_line(s);
    print_struct(cml);

	// free
	free_token(a);
	free_c_dptr(&s);
	free_c_dptr(&t);
	
	//  echo a > b | c > d || cat -e
	// leak cmds, cmd만 남음

	return (cml);
}

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

		cml = parse(context, str, result);

		// cml이 null일 경우 에러
		if (!cml)
		{
			printf("===============\n");
			printf("Error\n");
		}
		// 실행한 뒤 cml free
		free_cmd_line(cml);

		safe_free((void **) &str);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_context	context;

	if (!check_arg(argc, (const char **) argv))
		exit_with_status(ARG_ERR);
	if (!check_tty(0, 1, 2))
		exit_with_status(DEFAULT_FD_ERR);
	init_shell(&context, (const char **) envp);
	if (!print_intro())
		exit_with_status(PRINT_INTRO_ERR);
	readline_loop(&context);
	clear_envp_list(&(context.envp));
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (context.exit_status);
}
