#include "parser.h"
#include "libft.h"

int	is_redir2(char *s)
{
	if (ft_strncmp(s, "<", 2) || ft_strncmp(s, ">", 2) || ft_strncmp(s, "<<", 3) || ft_strncmp(s, ">>", 3))
		return (1);
	return (0);
}

// init
t_token *init_token(char *token)
{
	t_token *res;

	res = ft_malloc(sizeof(t_token), 1);
//printf("token res %p\n", res);
	res->data = ft_strdup(token);
	res->next = NULL;

	return (res);
}

// cmd에 붙여야함
t_redirect	*init_redirect(t_redir_type type, char *target)
{
	t_redirect *red;

	red = ft_malloc(sizeof(t_redirect), 1);
//printf("token red %p\n", red);
	red->type = type;
	red->target = ft_strdup(target);
	red->next = NULL;
	if (target == NULL || is_redir2(target))
		; // 에러 처리

	return (red);
}

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
//printf("token cml %p\n", cml);
	cml->next = NULL;
	cml->pipes = ft_malloc(sizeof(t_pipe), 1);
//printf("token pipes %p\n", cml->pipes);
	cml->pipes->num = 0;
	cml->pipes->type = PIPE;
	cml->pipes->cmds = NULL;
	// cml->pipes->cmds = ft_malloc(sizeof(t_cmd), 1);
	// cml->pipes->cmds->cmd = NULL;
	// cml->pipes->cmds->type = SINGLE_CMD;
	// cml->pipes->cmds->redir = ft_malloc(sizeof(t_redirect), 1);
	// cml->pipes->cmds->redir = NULL;
	return (cml);
}

// =====================================================
// add(with next)

void	add_token(t_token *token, char *data)
{
	t_token *new;
	t_token *cp;

	cp = token;
	if (token->data == NULL)
	{
		token->data = ft_strdup(data);
		return ;
	}
	while (cp->next)
		cp = cp->next;
	new = init_token(data);
	cp->next = new;
}

void	print_struct(t_cmd_line *cml)
{
	t_redirect *temp;
	size_t	i;
	int j;

	while (cml)
	{
		printf("pipe type: %d\n", cml->pipes->type);
		printf("pipe num: %zu\n", cml->pipes->num);
		i = 0;
		while (i < cml->pipes->num)
		{
			j = 0;
			while (cml->pipes->cmds[i]->cmd[j])
			{
				printf("cmds[%zu]->cmd[%d]: %s\n", i, j, cml->pipes->cmds[i]->cmd[j]);
				j++;
			}
			i++;
		}
		i = 0;
		while (i < cml->pipes->num)
		{
			temp = NULL;
			while (cml->pipes->cmds[i]->redir)
			{
				temp = cml->pipes->cmds[i]->redir;
				printf("%zu redir: %p\n", i, cml->pipes->cmds[i]->redir);
				printf("%zu type: %d\n", i, cml->pipes->cmds[i]->redir->type);
				printf("%zu target: %p\n", i, cml->pipes->cmds[i]->redir->target);
				cml->pipes->cmds[i]->redir = cml->pipes->cmds[i]->redir->next;
			}
			cml->pipes->cmds[i]->redir = temp;
			i++;
		}
		cml = cml->next;
		printf("==============\n");
	}
}

// echo a>b>c>d || echo a>b>vc>d (관계연산자 다음부터 리디렉션 저장 안됨, 파이프 다음에 이전 파이프 cmds 누적) 