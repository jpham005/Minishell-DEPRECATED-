/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:52:28 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/02/27 18:10:17 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_pipe_type check_pipe_type(char *s)
{
    if (strncmp(s, "&&", 3) == 0)
        return AND;
    if (strncmp(s, "||", 3) == 0)
        return OR;
    else
        return PIPE;
}

int is_pipe(char *s)
{
    if (strncmp(s, "&&", 3) == 0)
        || (strncmp(s, "||", 3) == 0)
        || (strncmp(s, "|", 2) == 0)
        return 1;
    return 0;
}

void    count_pipe(t_cmd_line *res, char **s)
{
    int i;
    int cnt;

    i = 0;
    cnt = 0;
    while (*(s + i))
    {
        if (is_pipe(*(s + i)))
            cnt++;
        i++;
    }
    add_pipe(&res, cnt); // 미리 파이프 개수 + 1만큼 cmd_line 덩어리를 만들어 둬야 함
}

void    fill_pipes(t_cmd_line *res, char **s)
{
    int i;
    int start;
    int end;
    int temp;
    char **str;

    i = 0;
    str = NULL:
    while (*(s + i))
    {
        start = i;
        while (is_pipe(*(s + i)) && *(s + i)) // 파이프나 NULL이 아닐 때까지 반복
            i++;
        end = i;
        temp = end - start + 1;
        str = ft_malloc(sizeof(char *), temp);
        while (--temp)
        {
            str[start] = s[start];
            start++;
        }
        str[start] = NULL;
        // 함수처리 해야 할 부분
        res->pipes->cmds->cmd = str;
        res->pipes->type = check_pipe_type(s[i]);
        res = res->next;
        i++;
    }
}

void    fill_redir(t_cmd_list *res, t_redir_type type)
{

}

void    fill_cmd_redir(t_cmd_list *res)
{
    int i;

    i = 0;
    while (res->pipes->cmds->cmd[i])
    {
        if (strncmp(res->pipes->cmds->cmd[i], "<", 2) == 0)
            fill_redir(res, REDIR_OUT);
        if (strncmp(res->pipes->cmds->cmd[i], ">", 2) == 0)
        if (strncmp(res->pipes->cmds->cmd[i], "<<", 3) == 0)
        if (strncmp(res->pipes->cmds->cmd[i], ">>", 3) == 0)
        i++;
    }
}

t_cmd_list  *token_to_cmd_line(char **s)
{
    t_cmd_list  *res;

    res = init_cmd_line();
    count_pipe(res, s);
    fill_pipes(res, s); // 여기까지 끝나면 cmds->cmd까지 채워져 있어야 함
    fill_cmd_redir(res); 
}


// int	main(void)
// {
	

// 	return (0);
// }