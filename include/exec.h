/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:45:13 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 07:54:04 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "envp.h"
# include "temphead.h"
# include "terminal.h"
# include "built_in.h"
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

typedef enum e_pipe_len_status
{
	IS_PIPE_CONTINUE = 0,
	IS_PIPE_END
}	t_pipe_len_status;

typedef struct s_in_out
{
	int	prev[2];
	int	curr[2];
	int	pipeline[2];
}	t_in_out;

typedef struct s_err_info
{
	char	*err_str;
	char	*err_target;
}	t_err_info;

void			executor(t_cmd_line *c_line, t_context *ctx);
int				exec_built_in(char **cmd, t_context *ctx, t_sh_built_in type);
int				handle_redir(t_redir *redir, t_context *context);
t_sh_built_in	is_built_in(char *cmd);
void			exec_cmd(char **cmd, t_context *context);
int				wait_all(pid_t *pids, size_t i, int ret);
void			init_in_out(t_in_out *in_out);
pid_t			exec_out(t_cmd *cmd, t_context *context, t_in_out *in_out);
void			child(t_cmd *cmd, t_context *context, t_in_out *in_out);
void			exec_parenthesis(char *str, t_context *context);
void			close_pipes(int pipes[2]);
int				handle_pipe(t_in_out *io, t_pipe_len_status st, t_context *ctx);

#endif