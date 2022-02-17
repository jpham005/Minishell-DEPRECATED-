/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:46:27 by jaham             #+#    #+#             */
/*   Updated: 2022/02/17 20:59:05 by jaham            ###   ########.fr       */
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
			add_history(str);
		context->exit_status = parse(str);
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
