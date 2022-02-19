#include "include/temphead.h"
#include "include/terminal.h"
#include <unistd.h>
#include <stdlib.h>

int	exec_pipes(t_pipe *pipes)
{
	write(1, "asdf\n", 5);
	return (0);
}

int	executer(t_cmd_line *cmd_line, t_context *context)
{
	while (cmd_line)
	{
		if (cmd_line->type == PIPE)
			context->exit_status = exec_pipes(cmd_line->pipes);
		else if ((cmd_line->type == AND) && !context->exit_status)
			context->exit_status = exec_pipes(cmd_line->pipes);
		else if ((cmd_line->type == OR) && context->exit_status)
			context->exit_status = exec_pipes(cmd_line->pipes);
		cmd_line = cmd_line->next;
	}
	return (1);
}

int main()
{
	t_cmd_line *head;
	t_context *context;

	head = malloc(sizeof(t_cmd_line));
	head->type = PIPE;
	head->next = malloc(sizeof(t_cmd_line));
	head->next->type = OR;
	head->next->next = malloc(sizeof(t_cmd_line));
	head->next->next->type = AND;
	head->next->next->next = NULL;
	executer(head, context);
}