/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:33:14 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/14 20:32:31 by hyeonpar         ###   ########.fr       */
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

typedef struct s_index
{
	int	i;
	int	j;
}	t_index;

typedef struct s_helper
{
	int	i;
	int	j;
	int	cnt;
	int	err;
}	t_helper;

void		set_values_str_helper(int *expanded, int *j);
char		**tokenizer(const char *line);
int			ft_is_space(int c);
t_token		*init_token(char *token);
t_token		*init_empty_token(void);
void		add_token(t_token *token, char *data);
t_token		*convert_dptr_to_struct(char **tokens);
char		**convert_token_to_dptr(t_token *head);
void		expand_asterisks(char ***str);
char		*expand_asterisk(char *arg, int *expanded);
void		expand_dollars(t_context *context, char ***str);
void		check_str(char **list, char **str, int *expanded);
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
void		check_dollar(int *dollar_flag, char *str, t_context *context);
int			is_env_var(char c);
int			count_dollar(char *s);
char		*is_envp(t_context *context, char *str, int start, int end);
void		ft_charjoin(char **new, char **s1, char c);
char		*del_quote(char *arg);
void		check_side(char **list, char *arg);
int			find_char(char *str, char s);
void		expand_estat(char **ex_val, char **new, char **t_s, t_context *ctx);
int			is_no_expand(char *str, t_index *idx, int *dollar_flag);
void		get_expand_val(int *i, char *str, t_context *ctx, char **ex_val);
void		get_new(char **ex_val, char **new, char **temp_s, int *i);
void		remove_par(char **str, int idx, t_cmd_line *res, int cmds_num);
int			get_start(const char *line, t_tokenizer *tool);
int			get_end(const char *line, t_tokenizer *tool);
void		ft_realloc_doublestr(char ***strs_ref, char *item);
int			ft_free_str(char **str);
int			is_redir(char *s, int *i);
int			fill_r(t_cmd_line *res, t_redir_type type, char *target, int j);
void		count_pipe(t_cmd_line *res, char **s);
int			fill_pipes(t_cmd_line *res, char **s);
void		check_str_helper(char **list, char **str, int *i, int *expanded);
int			fill_cmds(t_cmd_line *res, char **str);
void		init_cmds_and_redir(t_cmd_line *res);
int			is_redir2(char *s);
int			ft_is_set(char c, char *set);
char		get_quote(const	char *line, int idx);
int			delete_quote_1(char **str);
void		handle_zero_cnt(t_cmd_line *cp, int cnt, t_helper *idx);
t_token		*init_empty_token(void);
void		pass_dollar(char *str, t_index *idx);

#endif