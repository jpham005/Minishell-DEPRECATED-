/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:52:28 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/02/28 20:59:52 by hyeonpar         ###   ########.fr       */
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

int is_pipe(char *s) //
{
    if (s == NULL)
        return (0);
    if (
        (ft_strncmp(s, "&&", 2) == 0)
        || (ft_strncmp(s, "||", 2) == 0)
        // || (ft_strncmp(s, "|", 1) == 0)
    )
        return (1);
    return (0);
}

void    count_pipe(t_cmd_line *res, char **s) //
{
    int i;
    int pipe_num;
    int first;

    i = 0;
    pipe_num = 0;
    first = 1;
    while (*(s + i))
    {
        if (ft_strncmp(*(s + i), "|", 2) == 0)
            pipe_num++;
        if (is_pipe(*(s + i)))
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
    add_pipe(res, pipe_num + 1);
}

void    fill_pipes(t_cmd_line *res, char **s)
{
    int i;
    int j;
    int start;
    int temp;
    char **str;

    i = 0;
    while (*(s + i))
    {
        // str = NULL;
        j = 0;
        start = i;
        while (*(s + i) && !(is_pipe(*(s + i)))) // 관계연산자나 NULL이 아닐 때까지 반복
            i++;
        temp = i - start + 1;
        str = ft_malloc(sizeof(char *), temp);
        while (--temp)
            str[j++] = s[start++];
        str[j] = NULL;
        res->pipes->cmds->cmd = str; // 이걸 좀 수정해야하나싶음
        res = res->next;
        if (is_pipe(*(s + i)))
            res->pipes->type = check_pipe_type(s[i++]);
        // safe_free((void **) str);
        // ls|ls||ls||ls&&ls
    }
}

// 이미 malloc 되어있으므로 선언 없이 바로 할당해도 될 듯
// 처음 t_cmd_line을 생성할 때 내부 구조체 전부 초기화 해준다는 가정하에 작성
void    fill_redir(t_cmd_line *res, t_redir_type type, char *target)
{
    t_redirect  *new;

    if (res->pipes->cmds->redir == NULL)
        res->pipes->cmds->redir = init_redirect(type, target);
    else
    {
        new = init_redirect(type, target);
        while (res->pipes->cmds->redir->next)
            res->pipes->cmds->redir = res->pipes->cmds->redir->next;
        res->pipes->cmds->redir->next = new;
    }
}
/* res->pipes->cmds->cmd == 
    ["cat", "-en", "file1.txt", ">", "file2.txt", "cat", "file2.txt", NULL] */
/* cmd = 
    ["cat", "-en", "file1.txt", "cat", "file2.txt", NULL] */
/* res->pipes->cmds->cmd = cmd */
// 임시 리스트 추가
// ["cat", "-en", "file1.txt", "cat", "file2.txt", NULL]
// char *tmp = strjoin("Hyeonpar_jaham", res->pipes->cmds->cmd[i]);
// char **cmd = split(tmp, "Hyeonpar_jaham");
// res->pipes->cmds->cmd[i] = cmd;
void    fill_cmd_redir(t_cmd_line *res)
{
    int i;
    t_token *temp;

    i = 0;
    temp = NULL;
    while (res->pipes->cmds->cmd[i])
    {
        if (ft_strncmp(res->pipes->cmds->cmd[i], "<", 2) == 0)
            fill_redir(res, REDIR_OUT, res->pipes->cmds->cmd[++i]);
        else if (ft_strncmp(res->pipes->cmds->cmd[i], ">", 2) == 0)
            fill_redir(res, REDIR_IN, res->pipes->cmds->cmd[++i]);
        else if (ft_strncmp(res->pipes->cmds->cmd[i], "<<", 3) == 0)
            fill_redir(res, REDIR_HEREDOC, res->pipes->cmds->cmd[++i]);
        else if (ft_strncmp(res->pipes->cmds->cmd[i], ">>", 3) == 0)
            fill_redir(res, REDIR_APPEND, res->pipes->cmds->cmd[++i]);
        else
        {
            if (!temp)
                temp = init_token(res->pipes->cmds->cmd[i]);
            else
                add_token(temp, res->pipes->cmds->cmd[i]);
        }
        if (res->pipes->cmds->cmd[i] != NULL)
            i++;
    }
    res->pipes->cmds->cmd = convert_token_to_dptr(temp);
}

t_cmd_line  *token_to_cmd_line(char **s) // 토큰 구조체에 담기
{
    t_cmd_line  *res;

    res = init_cmd_line();
    count_pipe(res, s);
    fill_pipes(res, s);
    fill_cmd_redir(res);

    // 테스트 출력용
    // int i = 0;
    // while (res->pipes->cmds->cmd[i])
    //     printf("arg: %s\n", res->pipes->cmds->cmd[i++]);
    // i = 0;
    // while (res->pipes->cmds->redir)
    // {
    //     printf("redir: %d\n", res->pipes->cmds->redir->type);
    //     res->pipes->cmds->redir = res->pipes->cmds->redir->next;
    // }
    
    return (res);
}