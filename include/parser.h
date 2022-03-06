/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:33:14 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/07 03:52:40 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cmd_line.h"
# include "terminal.h"
# include <dirent.h>

typedef enum e_error
{
	SUCCESS = 0,
	SYNTAX_ERROR
}	t_error;

typedef struct s_token
{
	char			*data;
	struct s_token	*next;
}	t_token;

typedef struct s_tokenizer
{
	int		idx;
	int		qidx;
	int		start;
	int		prev;
	int		par;
	int		pidx;
	char	quote;
}	t_tokenizer;

char		**tokenizer(const char *line);
int			ft_is_space(int c);
t_token		*init_token(char *token);
t_token		*init_empty_token(void);
void		add_token(t_token *token, char *data);
t_token		*convert_dptr_to_struct(char **tokens);
char		**convert_token_to_dptr(t_token *head);
void		expand_asterisks(char ***str);
char		*expand_asterisk(char *arg);
void		expand_dollars(t_context *context, char **str);
void		check_str(char **list, char **str);
char		**current_path_ls(void);
int			is_asterisk(char *str);
t_cmd_line	*init_cmd_line(void);
t_cmd_line	*token_to_cmd_line(char **s);
void		add_pipe(t_cmd_line *res, int pipe_num);
t_redirect	*init_redirect(t_redir_type type, char *target);
void		print_struct(t_cmd_line *cml);
int			is_pipe(char *s);
void		free_cmd_line(t_cmd_line *cml);
void		free_token(t_token *token);
void		free_redir(t_redirect *redir);
char		*expand_asterisk_helper(char **list);
void		free_cmd_line_e(t_cmd_line *cml);
t_cmd_line	*parse(t_context *context, const char *str);
int			is_par(char *str);
void		split_str_i(char ***str, size_t *i);
int			check_syntax_err(char **str, t_context *context);
void		handle_syntax_err(t_context *context);
void		del_q(char *str);
void		check_dollar(int *dollar_flag, char *str);
int			is_env_var(char c);
int			count_dollar(char *s);
char		*is_envp(t_context *context, char *str, int start, int end);
void		ft_charjoin(char **new, char **s1, char c);

#endif