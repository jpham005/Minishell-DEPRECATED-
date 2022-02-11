/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:46:27 by jaham             #+#    #+#             */
/*   Updated: 2022/02/11 15:11:03 by jaham            ###   ########.fr       */
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

static int	readline_loop(t_context *context)
{
	char	*str;

	while (1)
	{
		str = ft_readline(context);
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
	t_context	context;

	if (!check_arg(argc, (const char **) argv))
		exit_with_status(ARG_ERR);
	if (!check_tty(STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO))
		exit_with_status(DEFAULT_FD_ERR);
	if (!init_context(&context, (const char **) envp))
		exit_with_status(INIT_CONTEXT_ERR);
	if (!print_intro())
		exit_with_status(PRT_INTRO_ERR);
	readline_loop(&context);
	clear_envp_list(&(context.envp));
	return (context.exit_status);
}
