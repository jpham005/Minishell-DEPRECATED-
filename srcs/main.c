/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:46:27 by jaham             #+#    #+#             */
/*   Updated: 2022/03/03 23:28:01 by hyeonpar         ###   ########.fr       */
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

void	free_struct(t_cmd_line *cml)
{
	t_cmd_line *temp;
	int i;
	
	i = 0;
	while (i < cml->pipes->num)
	{
		free_redir(cml->pipes->cmds[i]->redir);
		safe_free((void **) cml->pipes->cmds[i]->cmd);
		i++;
	}
	safe_free((void **) cml->pipes->cmds);
	while (cml)
	{
		temp = cml;
		cml = cml->next;
		safe_free((void **) &temp->pipes);
		safe_free((void **) &temp);
	}
}

t_cmd_line	*parse(t_context *context, const char *str, int *result)
{
	t_cmd_line *cml;
	char **t;
	char **s;
	t_token *a;

	t = tokenizer(str);
	a = convert_dptr_to_struct(t);
	s = convert_token_to_dptr(a);

	expand_dollars(context, s);
	//테스트
	// int i = 0;
	// while (*(s + i) != NULL)
	// {
	// 	printf("|%s|\n", *(s + i));
	// 	i++;
	// }
	expand_asterisks(context, s);
	// i = 0;
	// while (*(s + i) != NULL)
	// {
	// 	printf("|%s|\n", *(s + i));
	// 	i++;
	// }
	cml = token_to_cmd_line(s);
    print_struct(cml);
	safe_free((void **) t);
	free_token(a);
	free_struct(cml);

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

		cml = parse(context, str, result);
		// free로 파일 별도로 정리해서 만들자
		// 일단 누수 내버려두고 구현에 집중하자
		// 방금 주석한거
		// free_token(a);
		// free_cmd_line(cml);
		
		// context->exit_status = parse(str);

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
	return (context.exit_status);
}
