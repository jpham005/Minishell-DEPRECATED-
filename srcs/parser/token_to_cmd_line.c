/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:52:28 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/02/27 15:55:06 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

typedef enum e_pipe_type
{
    PIPE = 0,
    AND,
    OR
}   t_pipe_type;

t_pipe_type is_pipe(char *s)
{
    if (strncmp(s, "&&", 2) == 0)
        return AND;
    if (strncmp(s, "||", 2) == 0)
        return OR;
    else
        return PIPE;
}

static void    count_pipe(t_cmd_list *res, char **s)
{
    int i;
    int cnt;

    i = 0;
    cnt = 0;
    while (*(s + i))
    {
        if ((s[i][0] == &) && (s[i][1] == &) && (s[i][2] == '\0'))
            || ((s[i][0] == |) && (s[i][1] == |) && (s[i][2] == '\0'))
            || ((s[i][0] == |) && (s[i][2] == '\0'))
            cnt++;
        i++;
    }
    res->pipes = init_pipe(cnt);
}

t_cmd_list  *token_to_cmd_line(char **s)
{
    t_cmd_list  *res;

    count_pipe(res, s);
    insert_cmd();
    
}



// int main(void)
// {
//     char *s[5];

//     s[0] = "cd";
//     s[1] = "-";
//     s[2] = "||";
//     s[3] = "echo";
//     s[4] = "3";    



//     return (0);
// }