/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:46:27 by jaham             #+#    #+#             */
/*   Updated: 2022/02/08 16:36:50 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "context.h"
#include "init_terminal.h"
#include "envp.h"
#include "utils.h"

//parser part
static int	parse(const char *str)
{
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
	return (123);
}
//

static int	readline_loop(t_context *context)
{
	char	*str;

	while (1)
	{

		str = readline(MINISHELL_WITH_COLOR);
		if (!str)
			return (exit_with_status(END_TERM));
		if (*str)
			add_history(str);
		set_term_execute();
		context->exit_status = parse(str);
		signal(SIGINT, sig_int_handler_default);
		signal(SIGQUIT, SIG_IGN);
		safe_free((void **) &str);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_context	context;

	if (!check_arg(argc, (const char **) argv))
		return (exit_with_status(ARG_ERR));
	if (!check_tty(STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO))
		return (exit_with_status(DEFAULT_FD_ERR));
	if (!init_context(&context, (const char **) envp))
		return (exit_with_status(INIT_CONTEXT_ERR));
	if (!print_intro())
		return (exit_with_status(PRT_INTRO_ERR));
	if (!set_term_default())
		return (exit_with_status(SET_TERM_ERR));
	if (readline_loop(&context))
		return (exit_with_status(EXEC_ERR));
	clear_envp_list(&(context.envp));
	printf(DEFAULT_COLOR);
	return (context.exit_status);
}
