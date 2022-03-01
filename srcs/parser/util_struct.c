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
		; // 에러 처리
	red->next = NULL;

	return (red);
}

void	free_token(t_token *token)
{
	t_token *temp;

	while (token)
	{
		temp = token;
		token = token->next;
		safe_free((void **) &temp->data);
		safe_free((void **) temp);
	}
}

void	free_redir(t_redirect *redir) // target free 안 해줘도 되나?
{
	t_redirect *temp;

	while (redir)
	{
		temp = redir;
		redir = redir->next;
		safe_free((void **) temp);
	}
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

void	add_pipe(t_cmd_line *res, int pipe_num)
{
	t_cmd_line *new;

	new = init_cmd_line();
	new->pipes->num = pipe_num;
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
	// cml->pipes->cmds = ft_malloc(sizeof(t_cmd), 1);
	// cml->pipes->cmds->cmd = NULL;
	// cml->pipes->cmds->type = SINGLE_CMD;
	// cml->pipes->cmds->redir = ft_malloc(sizeof(t_redirect), 1);
	// cml->pipes->cmds->redir = NULL;
	return (cml);
}

void	free_cmd_line(t_cmd_line *cml) // test
{
	t_cmd_line *temp;

	// free_redir(cml->pipes->cmds->redir);
	safe_free((void **) &cml->pipes->cmds);
	safe_free((void **) &cml->pipes);
	while (cml)
	{
		temp = cml;
		cml = cml->next;
		safe_free((void **) temp);
	}
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

void	print_struct(t_cmd_line *cml)
{
	int i;
	int j;

	while (cml)
	{
		printf("pipe type: %d\n", cml->pipes->type);
		printf("pipe num: %zu\n", cml->pipes->num);
		i = 0;
		while (i < cml->pipes->num)
		{
			j = 0;
			while (cml->pipes->cmds[i].cmd[j])
			{
				printf("cmd[%d]: %s\n", i, cml->pipes->cmds[i].cmd[j]);
				j++;
			}
			i++;
		}
		// ls|ls||ls||ls&&ls
		// echo -n "asdasd $SHELL" > a| << b cat -e && cd || ls
		
		i = 0;
		while (i < cml->pipes->num)
		{
			while (cml->pipes->cmds[i].redir)
			{
				printf("cmd[%d] redir type: %d\n", i, cml->pipes->cmds[i].redir->type);
				printf("cmd[%d] redir target: %s\n", i, cml->pipes->cmds[i].redir->target);
				cml->pipes->cmds[i].redir = cml->pipes->cmds[i].redir->next;
			}
			i++;
		}
		cml = cml->next;
		printf("\n");
	}
}