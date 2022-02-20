#include "include/temphead.h"
#include "include/terminal.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "srcs/libft/libft.h"
#include <stdio.h>

int main()
{
	t_context *context = malloc(sizeof(t_context));
	context->envp = malloc(sizeof(t_envp_list));
	context->envp->key = "ASDF";
	context->envp->value = "zxf";
	context->envp->list_len = 1;
	context->envp->next = NULL;

	t_redirect *head;

	head = malloc(sizeof(t_redirect));
	head->target = "EOF";
	head->type = REDIR_HEREDOC;
	head->next = malloc(sizeof(t_redirect));

	head->next->target = "outfile";
	head->next->type = REDIR_APPEND;
	head->next->next = malloc(sizeof(t_redirect));

	head->next->next->target = "infile";
	head->next->next->type = REDIR_IN;
	head->next->next->next = NULL;

	int in[2];
	int out;

	in[0] = 0;
	in[1] = 0;
	out = 1;

	t_pipe	*pipe = malloc(sizeof(t_pipe));
	pipe->cmds = malloc(sizeof(t_cmd));
	pipe->len = 1;
	pipe->type = SINGLE_CMD;
	exec_single_cmd(pipe, in, out, context);
}
