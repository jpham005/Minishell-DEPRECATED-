/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:33:14 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/02/28 02:12:59 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h> // size_t
# include <terminal.h>
# include <dirent.h>

// enum
typedef enum e_error
{
    SUCCESS = 0,
    SYNTAX_ERROR
}   t_error;

typedef enum e_cmd_type
{
    SINGLE_CMD = 0,
    PARENTHESIS
}   t_cmd_type;

typedef enum e_pipe_type
{
    PIPE = 0,
    AND,
    OR
}   t_pipe_type;

typedef enum e_redir_type
{
    REDIR_IN = 0, // >
    REDIR_HEREDOC, // <<
    REDIR_OUT, // <
    REDIR_APPEND // >>
}   t_redir_type;

// 구조체
typedef struct s_redirect
{
    t_redir_type type;
    char *target;
    struct s_redirect *next;
}   t_redirect;
// 임시 string linked list
/*
    char *__STRING
    string_list *next;
*/
typedef struct s_cmd // 초기화할 때 여기까지만 ft_malloc함
{
    // likend list
    // ["cat" -> "-en" -> "file1.txt" -> ">" -> "file2.txt" -> "cat" -> "file2.txt" -> NULL]
    // ["cat" -> "-en" -> "file1.txt" -> "cat" -> "file2.txt" -> NULL]
    char **cmd; // 여기도 마찬가지 NULL 초기화
    t_redirect *redir; // 처음엔 여기 NULL로 초기화할 것
    t_cmd_type type;
}   t_cmd;

typedef struct s_pipe
{
    t_cmd *cmds;
    size_t num;
    t_pipe_type type;
}   t_pipe;

typedef struct s_cmd_line
{
    t_pipe *pipes;
    struct s_cmd_line *next;
}   t_cmd_line;

// s_cmd의 **cmd 사용 전 사용할 구조체
typedef struct s_token
{
    char *data;
    struct s_token *next;

}   t_token;

typedef struct	s_tokenizer
{
	int		idx;
	int		qidx;
	int		start;
	int		prev;
	char	quote;
}				t_tokenizer;

char    **tokenizer(char *line);
int		ft_is_space(int c);
t_token *init_token(char *token);
void	add_token(t_token *token, char *data);
t_token	*convert_dptr_to_struct(char **tokens);
char	**convert_token_to_dptr(t_token *head);
void	expand_tokens(char *str, t_context *context);
char	*expand_asterisk(char *arg);
char	**par2(char **pars_str, t_context *context);
char	**par3(char **pars_str, int flag_q, t_context *context);
void	check_str(char **list, char **str, int *arr);
char	**current_path_ls(void);
int		is_asterisk(char *str);
char	**par4(char **pars_s, char *e_v, int ss_i, t_context *ctx);
t_cmd_line	*init_cmd_line(void);
t_cmd_line  *token_to_cmd_line(char **s);
void	add_pipe(t_cmd_line *res, int num);
t_redirect	*init_redirect(t_redir_type type, char *target);

#endif