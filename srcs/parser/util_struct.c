#include "parser.h"
#include "libft.h"

// libft에 넣어도 될 듯
int	is_redir(char *s)
{
	if (ft_strncmp(s, "<", 2) || ft_strncmp(s, ">", 2) || ft_strncmp(s, "<<", 3) || ft_strncmp(s, ">>", 3))
		return (1);
	return (0);
}

// init
t_token *init_token(char *token) //
{
	t_token *res;

	res = ft_malloc(sizeof(t_token), 1);
	res->data = token;
	res->next = NULL;

	return (res);
}

// cmd에 붙여야함
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

// t_pipe	*init_pipe(t_cmd_line *res, int num)
// {
// 	t_pipe *pipe;
// 	int i;

// 	i = num;
// 	pipe = ft_malloc(sizeof(t_pipe), 1);
// 	res->pipe->cmds = NULL;
// 	res->pipe->num = num; // 개수 고정
// 	res->pipe->type = PIPE;
// 	res->next = NULL;
// 	while (i--)
// 		add_pipe(res, num);

// 	return (pipe);
// }

void	add_pipe(t_cmd_line *res, int num) //
{
	t_cmd_line *new;

	new = init_cmd_line();
	new->pipes->num = num;
	while (res->next)
		res = res->next;
	res->next = new;
}

// 여기서 하위 구조체까지 전부 말록해서 접근 가능하게 해둘 것임
t_cmd_line	*init_cmd_line(void) // 
{
	t_cmd_line *cml;

	cml = ft_malloc(sizeof(t_cmd_line), 1);
	cml->next = NULL;
	cml->pipes = ft_malloc(sizeof(t_pipe), 1);
	cml->pipes->num = 0;
	cml->pipes->type = PIPE;
	cml->pipes->cmds = ft_malloc(sizeof(t_cmd), 1);
	cml->pipes->cmds->cmd = NULL;
	cml->pipes->cmds->type = SINGLE_CMD;
	cml->pipes->cmds->redir = ft_malloc(sizeof(t_redirect), 1);
	cml->pipes->cmds->redir = NULL;
	return (cml);
}

void	*free_cmd_line(t_cmd_line *cml) // test
{
	safe_free((void **) &cml->pipes->cmds->redir); // 넥스트 노드 돌면서 free
	safe_free((void **) &cml->pipes->cmds);
	safe_free((void **) &cml->pipes);
	safe_free((void **) &cml); // 넥스트 노드 돌면서 free
}

// =====================================================
// add(with next)

void	add_redirect(t_redirect *red, t_redir_type type, char *target)
{
	t_redirect *new;

	new = init_redirect(type, target);
	red->next = new;
}

void	add_token(t_token *token, char *data)
{
	t_token *new;

	while (token->next)
		token = token->next;
	new = init_token(data);
	token->next = new;
}

// t_cmd_line	*add_cmd_line(t_cmd_line *cml, t_pipe *pipe)
// {
// 	t_cmd_line *new;

// 	new = init_cmd_line(pipe);
// 	cml->next = new;

// 	return (cml);
// }