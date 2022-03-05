/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:54:45 by jaham             #+#    #+#             */
/*   Updated: 2022/03/05 15:26:55 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "utils.h"
#include "libft.h"
#include "exec.h"
#include "built_in.h"

#include <sys/wait.h> // temp
#include <stdlib.h>
#include <stdio.h>
//parser part
static int	parse(const char *str)
{
	int	pid;
	int	status;

	if (!ft_strncmp("loop", str, 5))
	{
		pid = fork();
		if (!pid)
		{
			signal(SIGINT, SIG_DFL);
			execve("jaham_test/loop", NULL, NULL);
		}
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

int	readline_loop(t_context *context)
{
	char	*str;

	while (1)
	{
		str = ft_readline(context, NULL);
		if (!str)
			exit(exit_with_status(END_TERM));
		if (!check_str(str, context))
		{
			safe_free((void **) &str);
			continue ;
		}
		context->exit_status = parse(str);

		t_cmd_line	*cmd_line = malloc(sizeof(t_cmd_line));
		cmd_line->pipes = malloc(sizeof(t_pipe));
		cmd_line->pipes->type = PIPE;
		cmd_line->pipes->len = 3;
		cmd_line->pipes->cmds = malloc(sizeof(t_cmd *) * 4);
		cmd_line->pipes->cmds[0] = malloc(sizeof(t_cmd));
		cmd_line->pipes->cmds[0]->type = SINGLE_CMD;
		cmd_line->pipes->cmds[0]->redir = NULL;
		cmd_line->pipes->cmds[0]->redir = malloc(sizeof(t_redirect));
		cmd_line->pipes->cmds[0]->redir->next = NULL;
		cmd_line->pipes->cmds[0]->redir->target = "infile";
		cmd_line->pipes->cmds[0]->redir->type = REDIR_IN;
		cmd_line->pipes->cmds[0]->cmd = ft_split("cat", ' ');
		cmd_line->pipes->cmds[1] = malloc(sizeof(t_cmd));
		cmd_line->pipes->cmds[1]->type = SINGLE_CMD;
		cmd_line->pipes->cmds[1]->redir = NULL;
		cmd_line->pipes->cmds[1]->cmd = ft_split("asdf fadfsa saf", ' ');
		cmd_line->pipes->cmds[2] = malloc(sizeof(t_cmd));
		cmd_line->pipes->cmds[2]->type = SINGLE_CMD;
		cmd_line->pipes->cmds[2]->redir = NULL;
		cmd_line->pipes->cmds[2]->cmd = ft_split("ls", ' ');

		cmd_line->next = NULL;

		//cmd_line->next = malloc(sizeof(t_cmd_line));
		//cmd_line->next->pipes = malloc(sizeof(t_pipe));
		//cmd_line->next->pipes->type = AND;
		//cmd_line->next->pipes->len = 3;
		//cmd_line->next->pipes->cmds = malloc(sizeof(t_cmd) * cmd_line->next->pipes->len);
		
		//cmd_line->next->pipes->cmds[0]->type = SINGLE_CMD;
		//cmd_line->next->pipes->cmds[0]->cmd = ft_split("ls", ' ');
		//cmd_line->next->pipes->cmds[0]->redir = NULL;
		// cmd_line->next->pipes->cmds[0]->redir = malloc(sizeof(t_redirect));
		// cmd_line->next->pipes->cmds[0]->redir->type = REDIR_IN;
		// cmd_line->next->pipes->cmds[0]->redir->target = "infile";
		// cmd_line->next->pipes->cmds[0]->redir->next = NULL;

		//cmd_line->next->pipes->cmds[1]->type = SINGLE_CMD;
		//cmd_line->next->pipes->cmds[1]->cmd = ft_split("cat -e", ' ');
		// cmd_line->next->pipes->cmds[1]->redir = NULL;
		//cmd_line->next->pipes->cmds[1]->redir = malloc(sizeof(t_redirect));
		//cmd_line->next->pipes->cmds[1]->redir->type = REDIR_OUT;
		//cmd_line->next->pipes->cmds[1]->redir->target = "outfile";
		//cmd_line->next->pipes->cmds[1]->redir->next = NULL;

		//cmd_line->next->pipes->cmds[2]->type = SINGLE_CMD;
		//cmd_line->next->pipes->cmds[2]->cmd = ft_split("cat -e", ' ');
		//cmd_line->next->pipes->cmds[2]->redir = NULL;
		// cmd_line->next->pipes->cmds[2]->redir = malloc(sizeof(t_redirect));
		// cmd_line->next->pipes->cmds[2]->redir->type = REDIR_IN;
		// cmd_line->next->pipes->cmds[2]->redir->target = "infile";
		// cmd_line->next->pipes->cmds[2]->redir->next = NULL;


		executor(cmd_line, context, NULL);
		fprintf(stdout, "exit status %d\n", context->exit_status);
		safe_free((void **) &str);
	}
	return (0);
}
