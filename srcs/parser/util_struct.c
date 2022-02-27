#include "parser.h"
#include "libft.h"

// libft에 넣어도 될 듯
int	is_redir(char *s)
{
	if (strncmp(s, "<", 2) || strncmp(s, ">", 2) || strncmp(s, "<<", 3) || strncmp(s, ">>", 3))
		return (1);
	return (0);
}

// init
t_token *init_token(char *token)
{
	t_token *res;

	res = ft_malloc(sizeof(t_token), 1);
	res->data = token;
	res->next = NULL;

	return (res);
}

t_redirect	*init_redirect(t_redir_type type, char *target)
{
	t_redirect *red;

	red = ft_malloc(sizeof(t_redirect), 1);
	red->type = type;
	red->target = target;
	if (target == NULL || is_redir(target))
		; // result = SYNTAX_ERROR // syntax error near unexpected token `newline'
		// 여러 개의 token이 target이 될 수 있는가?
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

t_pipe	*init_pipe(t_cmd_line *res, int num)
{
	t_pipe *pipe;
	int i;

	i = num;
	pipe = ft_malloc(sizeof(t_pipe), 1);
	res->pipe->cmds = NULL;
	res->pipe->num = num; // 개수 고정
	res->pipe->type = PIPE;
	res->next = NULL;
	while (i--)
		add_pipe(res, num);

	return (pipe);
}

void	add_pipe(t_cmd_line **res, int num)
{
	t_cmd_line *new;

	new = ft_malloc(sizeof(t_cmd_line), 1);
	new->pipes = ft_malloc(sizeof(t_pipe), 1);
	new->pipes->cmds = NULL;
	new->pipes->num = num;
	new->pipes->type = PIPE;
	new->next = NULL;
	// 요런 걸로 간단히 할 수 있긴 할 듯
	// new = init_pipe(num);
	while (*res)
		*res = &((*res)->next);
	*res = new;

t_cmd_line	*init_cmd_line(void)
{
	t_cmd_line *cml;

	cml = ft_malloc(sizeof(t_cmd_line), 1);
	cml->pipes = NULL;
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

void	add_token(t_token **token, char *data)
{
	t_token *new;

	while (*token)
		token = &((*token)->next);
	new = init_token(data);
	*token = new;
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

// ========================================================================