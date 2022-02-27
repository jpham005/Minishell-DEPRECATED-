#include "parser.h"
#include "libft.h"

// init
t_token *init_token(void)
{
	t_token *res;

	res = ft_malloc(sizeof(t_token), 1);
	res->data = NULL;
	res->next = NULL;

	return (res);
}

t_redirect	*init_redirect(t_redir_type type, char *target)
{
	t_redirect *red;

	red = ft_malloc(sizeof(t_redirect), 1);
	red->type = type;
	red->target = target;
	red->next = NULL;

	return (red);
}

t_cmd	*init_cmd(t_redirect *red)
{
	t_cmd *cmd;

	cmd = ft_malloc(sizeof(t_cmd), 1);
	cmd->cmd[0][0] = '\0';
	cmd->cmd[1] = NULL;
	cmd->redir = red;
	cmd->type = SINGLE_CMD;

	return (cmd);
}

t_pipe	*init_pipe(t_cmd *cmd)
{
	t_pipe *pipe;

	pipe = ft_malloc(sizeof(t_pipe), 1);
	pipe->cmds = cmd;
	pipe->num = 0;
	pipe->type = PIPE;

	return (pipe);
}

t_cmd_line	*init_cmd_line(t_pipe *pipe)
{
	t_cmd_line *cml;

	cml = ft_malloc(sizeof(t_cmd_line), 1);
	cml->pipes = pipe;
	cml->next = NULL;

	return (cml);
}

// =====================================================
// add(with next)

void	add_redirect(t_redirect *red, t_redir_type type, char *target)
{
	t_redirect *new;

	new = init_redirect(type, target);
	red->next = new;
}

t_cmd_line	*add_cmd_line(t_cmd_line *cml, t_pipe *pipe)
{
	t_cmd_line *new;

	new = init_cmd_line(pipe);
	cml->next = new;

	return (cml);
}

// add(without next)
// t_cmd	*add_cmd(t_cmd *cmd, char *s, t_redirect *redir, t_cmd_type type)
// {
// 	// token 연결리스트 만들기
// 	;
// }

t_pipe	*add_pipe(t_pipe *pipe, t_cmd *cmds, size_t num, t_pipe_type type)
{
	pipe->cmds = cmds;
	pipe->num = num;
	pipe->type = type;

	return (pipe);
}