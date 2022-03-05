/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:52:28 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/05 15:34:32 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 구조체 안의 구조체를 처리하려고 하다 보니 잘 되지 않음.
// 포인터와 구조체 사용에 여전히 익숙하지 않은 듯.
// res->pipes로 이어지는 내용물에 어떻게 접근해야 할 지, 담는 방식 적절한지
// 한 번 더 확인 필요할 듯함.

// cmd -> 리디렉션, 파이프(관계연산자) 나오기 전까지 뒤 전부 인자로 cmd에 담음
// 인자, 파일은 전부 아스터리스크(괄호 flag면 확장 x). 달러(괄호 없거나 대괄호 flag만 허용) 확장 가능해야 함
// 달러는 해당하는 환경변수가 없으면 아무것도 없는 것으로 치환한다
// 파일 뒤에 아스터리스크가 오면 에러처리 ambiguous redirect
// quote flag 살아있으면 입력 더 받는다
#include "parser.h"
#include "libft.h"

t_pipe_type check_pipe_type(char *s)
{
    if (ft_strncmp(s, "&&", 2) == 0)
        return AND;
    if (ft_strncmp(s, "||", 2) == 0)
        return OR;
    else
        return PIPE;
}

int is_pipe(char *s)
{
    if (s == NULL)
        return (0);
    if (
        (ft_strncmp(s, "&&", 2) == 0)
        || (ft_strncmp(s, "||", 2) == 0)
    )
        return (1);
    return (0);
}

void    count_pipe(t_cmd_line *res, char **s)
{
    int i;
    int pipe_num;
    int first;

    i = 0;
    pipe_num = 0;
    first = 1;
    while (s[i])
    {
        if (ft_strncmp(s[i], "|", 2) == 0)
            pipe_num++;
        if (is_pipe(s[i]))
        {
            if (first)
            {
                res->pipes->num = pipe_num + 1;
                first--;
            }
            else
                add_pipe(res, pipe_num + 1);
            pipe_num = 0;
        }
        i++;
    }
    if (first)
        res->pipes->num = pipe_num + 1;
    else
        add_pipe(res, pipe_num + 1);
}

t_token    *init_empty_token(void)
{
    t_token *temp;

    temp = ft_malloc(sizeof(t_token), 1);
    temp->data = NULL;
    temp->next = NULL;
    return (temp);
}

void    init_cmds_and_redir(t_cmd_line *res)
{
    int i;

    i = 0;
    res->pipes->cmds = ft_malloc(sizeof(t_cmd *), res->pipes->num);
    while (i < res->pipes->num)
    {
        res->pipes->cmds[i] = ft_malloc(sizeof(t_cmd), 1);
        i++;
    }
    i = 0;
    while (i < res->pipes->num)
    {
        res->pipes->cmds[i]->redir = ft_malloc(sizeof(t_redirect), 1);
        // res->pipes->cmds[i]->redir = NULL;
        res->pipes->cmds[i]->redir->target = NULL;
        res->pipes->cmds[i]->redir->next = NULL;
        i++;
    }
}

void    fill_cmds(t_cmd_line *res, char **str)
{
    t_token *temp;
    int i;
    int j;

    i = -1;
    j = 0;
    temp = init_empty_token();
    init_cmds_and_redir(res);
    while (str[++i])
    {
        if (ft_strncmp(str[i], "|", 2) == 0)
        {
            res->pipes->cmds[j]->cmd = convert_token_to_dptr(temp);
            res->pipes->cmds[j]->type = SINGLE_CMD;
            free_token(temp);
            temp = init_empty_token();
            j++;
        }
        else
            add_token(temp, str[i]);
    }
    res->pipes->cmds[j]->cmd = convert_token_to_dptr(temp);
    res->pipes->cmds[j]->type = SINGLE_CMD;
    free_token(temp);
}

void    fill_pipes(t_cmd_line *res, char **s)
{
    int i;
    int j;
    int start;
    int temp;
    char **str;

    i = 0;
    while (s[i])
    {
        j = 0;
        start = i;
        while (s[i] && !(is_pipe(s[i]))) // 관계연산자나 NULL이 아닐 때까지 반복
            i++;
        temp = i - start + 1;
        str = ft_malloc(sizeof(char *), temp);
        while (--temp)
            str[j++] = ft_strdup(s[start++]);
        str[j] = NULL;
        fill_cmds(res, str);
        if (res->next)
            res = res->next;
        if (is_pipe(s[i]))
            res->pipes->type = check_pipe_type(s[i++]);
        // if (!s[i]) // 관계연산자 뒤가 널일 때 처리를 위함
        // {
        //     str = ft_malloc(sizeof(char *), 1);
        //     str[0] = NULL;
        //     fill_cmds(res, str);
        // }
        free_c_dptr(&str);
    }
}

void    fill_redir(t_cmd_line *res, t_redir_type type, char *target, int j)
{
    t_redirect  *new;
    t_redirect  *temp;

    if (res->pipes->cmds[j]->redir->target == NULL)
        res->pipes->cmds[j]->redir = init_redirect(type, target);
    else
    {
        temp = res->pipes->cmds[j]->redir;
        new = init_redirect(type, target);
        while (res->pipes->cmds[j]->redir->next)
            res->pipes->cmds[j]->redir = res->pipes->cmds[j]->redir->next;
        res->pipes->cmds[j]->redir->next = new;
        res->pipes->cmds[j]->redir = temp;
    }
}

void    fill_cmd_redir(t_cmd_line *res)
{
    t_token *temp;
    t_cmd_line *cp;
    int i;
    int j;

    cp = res;
    while (cp)
    {
        j = -1;
        while (++j < cp->pipes->num)
        {
            temp = init_empty_token();
            i = 0;
            while (cp->pipes->cmds[j]->cmd[i])
            {
                if (ft_strncmp(cp->pipes->cmds[j]->cmd[i], "<", 2) == 0)
                    fill_redir(cp, REDIR_OUT, cp->pipes->cmds[j]->cmd[++i], j);
                else if (ft_strncmp(cp->pipes->cmds[j]->cmd[i], ">", 2) == 0)
                    fill_redir(cp, REDIR_IN, cp->pipes->cmds[j]->cmd[++i], j);
                else if (ft_strncmp(cp->pipes->cmds[j]->cmd[i], "<<", 3) == 0)
                    fill_redir(cp, REDIR_HEREDOC, cp->pipes->cmds[j]->cmd[++i], j);
                else if (ft_strncmp(cp->pipes->cmds[j]->cmd[i], ">>", 3) == 0)
                    fill_redir(cp, REDIR_APPEND, cp->pipes->cmds[j]->cmd[++i], j);
                else
                    add_token(temp, cp->pipes->cmds[j]->cmd[i]);
                if (cp->pipes->cmds[j]->cmd[i] != NULL)
                    i++;
            }
            free_c_dptr(&cp->pipes->cmds[j]->cmd);
            cp->pipes->cmds[j]->cmd = convert_token_to_dptr(temp);
            free_token(temp);
        }
        cp = cp->next;
    }
}

void	delete_quote_2(char **str, int len, int i)
{
	char *s;
	int	j;
	char quote;

	s = ft_malloc(sizeof(char), len + 1);
	j = -1;
	quote = 0;
	len = 0;
	while(str[i][++j])
	{
		if (quote == 0 && (str[i][j] == '\'' || str[i][j] == '\"'))
		{
			quote = str[i][j];
			continue;
		}
		else if ((quote == '\'' && str[i][j] == '\'') || (quote == '\"' && str[i][j] == '\"'))
		{
			quote = 0;
			continue;
		}
		s[len++] = str[i][j];
	}
	s[len] = '\0';
	safe_free((void **) &str[i]);
	str[i] = ft_strdup(s);
	safe_free((void **) &s);
}

int delete_quote_1(char **str)
{
	int i;
	int	j;
	int	quote;
	int	len;

	i = -1;
	while (str[++i])
	{
		j = -1;
		quote = 0;
		len = 0;
		while(str[i][++j])
		{
			if (quote == 0 && (str[i][j] == '\'' || str[i][j] == '\"'))
			{
				quote = str[i][j];
				continue;
			}
			else if ((quote == '\'' && str[i][j] == '\'') || (quote == '\"' && str[i][j] == '\"'))
			{
				quote = 0;
				continue;
			}
			len++;
		}
		if (quote)
            return (0);
		delete_quote_2(str, len, i);
	}
    return (1);
}

t_cmd_line  *token_to_cmd_line(char **s)
{
    t_cmd_line  *res;

    if (!delete_quote_1(s))
    {
        res = NULL;
        return (res);
    }
    res = init_cmd_line();
    count_pipe(res, s);
    fill_pipes(res, s);
    fill_cmd_redir(res);

    return (res);
}