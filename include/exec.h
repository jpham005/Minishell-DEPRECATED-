/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:45:13 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 21:49:24 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "built_in.h"
# include "cmd_line.h"
# include "envp.h"
# include "terminal.h"
# include <sys/stat.h>

# define PERMISSION_ERR_MSG ": Permission denied\n"
# define NOT_FOUND_ERR_MSG ": No such file or directory\n"
# define CMD_NOT_FOUND_ERR_MSG ": command not found\n"
# define IS_DIR_ERR_MSG ": is a directory\n"

typedef struct stat	t_stat;

typedef enum e_file_stat
{
	NOT_FOUND = 0,
	IS_DIR,
	NO_PERMISSION
}	t_file_stat;

typedef enum e_isexit
{
	RETURN,
	EXIT
}	t_isexit;

typedef enum e_pipe_bool
{
	NO_PIPE,
	DO_PIPE
}	t_pipe_bool;

typedef struct s_in_out
{
	int	in;
	int	out;
}	t_in_out;

typedef struct s_err_info
{
	char	*err_str;
	char	*err_target;
}	t_err_info;

void			executor(t_cmd_line *c_line, t_context *ctx, t_in_out *io);
int				exec_built_in(char **cmd, t_context *ctx, t_sh_built_in type);
int				handle_redirection(t_redirect *redi, t_context *c, t_in_out *i);
t_sh_built_in	is_built_in(char *cmd);
void			exec_cmd(char **cmd, t_context *context);
int				wait_all(pid_t *pids, size_t i, int ret);
void			init_in_out(int in[2], int *out);
void			dup_errs(t_err_info *err_info, char *target, int status);
void			set_in_out(int in[2], int out, t_in_out *in_out);
int				close_and_pipe(int in[2]);
int				is_heredoc_str(char *s1, char *s2);
pid_t			exec_out(t_cmd *cmd, t_context *context, t_in_out *in_out);
void			exec_parenthesis(char *str, t_context *context, t_in_out *io);
void			close_pipes(int pipes[2]);
int				handle_pipe(t_in_out *io, t_pipe_bool st, t_context *ctx);
int				replace_stdio(t_in_out *in_out, t_context *context);
pid_t			exec_fork_out(t_cmd *cmd, t_context *context, t_in_out *in_out);
pid_t			exec_fork(t_cmd *cmd, t_context *context, t_in_out *in_out);
int				handle_redir_heredoc(int in[2], t_redirect *redir, \
										t_err_info *info, t_context *context);
int				exec_pipes(t_pipe *pipes, t_context *context, t_in_out *in_out);

#endif