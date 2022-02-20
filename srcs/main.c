/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:46:27 by jaham             #+#    #+#             */
/*   Updated: 2022/02/21 03:46:17 by jaham            ###   ########.fr       */
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
#include "temphead.h"
#include "exec.h"
#include <stdlib.h>
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

	// make cmd_line for test. (length 1)
	t_cmd_line	*cmd_line = malloc(sizeof(t_cmd_line));
	cmd_line->type = PIPE;
	cmd_line->pipes = malloc(sizeof(t_pipe));
	cmd_line->next = NULL;

	// set pipe struct
	cmd_line->pipes->type = SINGLE_CMD;
	cmd_line->pipes->len = 3;

	// set redirection
	t_redirect *redir = malloc(sizeof(t_redirect));
	redir->target = "infile";
	redir->type = REDIR_IN;
	redir->next = malloc(sizeof(t_redirect));

	redir->next->target = "EOF";
	redir->next->type = REDIR_HEREDOC;
	// redir->next->next = NULL;
	redir->next->next = NULL;
	// outfile test
	//redir->next->next = malloc(sizeof(t_redirect));
	//redir->next->next->target = "outfile";
	//redir->next->next->type = REDIR_OUT;
	//redir->next->next->next = NULL;

	// set cmds
	t_cmd	*cmds = malloc(sizeof(t_cmd) * 3);
	cmds[0].redir = redir;
	cmds[0].cmd = ft_split("/bin/cat", ' ');
	cmds[1].cmd = ft_split("/bin/cat", ' ');
	//cmds[1].redir = NULL;
	cmds[1].redir = malloc(sizeof(t_redirect));
	cmds[1].redir->type = REDIR_OUT;
	cmds[1].redir->target = "outfile2";
	cmds[1].redir->next = NULL;
	//cmds[2]
	cmds[2].redir = NULL;
	cmds[2].cmd = ft_split("/bin/ls", ' ');

	cmd_line->pipes->cmds = cmds;

	executer(cmd_line, &context);
	// print exit status
	printf("%d\n", context.exit_status);
	// test end
	clear_envp_list(&(context.envp));
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (context.exit_status);
}
