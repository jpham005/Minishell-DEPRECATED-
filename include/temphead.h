/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temphead.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:49:29 by jaham             #+#    #+#             */
/*   Updated: 2022/02/20 15:22:11 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPHEAD_H
# define TEMPHEAD_H

# include <unistd.h>

typedef enum e_built_in
{
	SH_CD = 0,
	SH_ECHO,
	SH_ENV,
	SH_EXIT,
	SH_EXPORT,
	SH_PWD,
	SH_UNSET,
	SH_NONE
}	t_built_in;

typedef enum e_pipe_type // will use hyeonpar's
{
	PIPE = 0,
	AND,
	OR
}	t_pipe_type;

typedef enum e_redir_type
{
	REDIR_IN = 0,
	REDIR_HEREDOC,
	REDIR_OUT,
	REDIR_APPEND
}	t_redir_type;

typedef enum e_cmd_type
{
	SINGLE_CMD = 0,
	PARENTHESIS
}	t_cmd_type;
// 하나의 프로세스(s_parse) 단위에서 여러 개의 리다이렉트(파일입출력) 처리가 이루어질 수 있기 때문에 여러 개 보내야 함
typedef struct s_redirect
{
    t_redir_type	type; // <, << / >, >>
    char *target; // if heredoc, limit_string
    struct s_redirect *next;
}   t_redirect;

typedef struct s_cmd
{
    char **cmd; // echo -e "helloworld"
    t_redirect *redir; // 리다이렉트 모음
    // int pipe[2];
}   t_cmd;

typedef struct s_pipe
{
    t_cmd *cmds; // struct 구조체
    size_t	len; // cmd의 개수
    t_cmd_type	type; // is parenthesis or not
}   t_pipe;

typedef struct s_cmd_line
{
    t_pipe				*pipes; // struct 구조체
    t_pipe_type			type; // 논리 연산자(&&, ||) 타입(0, 1, 2)
    struct s_cmd_line	*next;
}	t_cmd_line;

#endif