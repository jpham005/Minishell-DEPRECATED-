/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temphead.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:49:29 by jaham             #+#    #+#             */
/*   Updated: 2022/02/25 11:38:31 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPHEAD_H
# define TEMPHEAD_H

# include <unistd.h>

typedef enum e_pipe_type // will use hyeonpar's
{
	PIPE = 0, // | or none
	AND, // &&
	OR // ||
}	t_pipe_type;

typedef enum e_redir_type
{
	REDIR_IN = 0, // <
	REDIR_HEREDOC, // <<
	REDIR_OUT, // >
	REDIR_APPEND // >>
}	t_redir_type;

typedef enum e_cmd_type
{
	SINGLE_CMD = 0, // without parenthesis
	PARENTHESIS // with ex. (ls || ls)
}	t_cmd_type;
// 하나의 프로세스(s_parse) 단위에서 여러 개의 리다이렉트(파일입출력) 처리가 이루어질 수 있기 때문에 여러 개 보내야 함
typedef struct s_redir
{
    t_redir_type	type; // <, << / >, >>
    char *target; // if heredoc, limit_string
    struct s_redir *next; // NULL if none
}   t_redir;

typedef struct s_cmd
{
    char		**cmd; // echo -e "helloworld"
    t_redir		*redir; // 리다이렉트 모음
	t_cmd_type	type; // normal || parenthesis ()
    // int pipe[2];
}   t_cmd;

typedef struct s_pipe
{
    t_cmd *cmds; // struct 구조체
    size_t	len; // cmd의 개수
}   t_pipe;

typedef struct s_cmd_line
{
    t_pipe				*pipes; // struct 구조체
    t_pipe_type			type; // 논리 연산자(&&, ||) 타입(0, 1, 2)
    struct s_cmd_line	*next;
}	t_cmd_line;

#endif