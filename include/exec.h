/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:45:13 by jaham             #+#    #+#             */
/*   Updated: 2022/02/24 15:47:50 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "envp.h"
#include "temphead.h"
#include "terminal.h"

#define NOT_BUILT_IN -1

typedef enum e_isexit
{
	RETURN,
	EXIT
}	t_isexit;

typedef struct s_in_out
{
	int	infile;
	int	outfile;
}	t_in_out;

typedef struct s_err_info
{
	char	*err_str;
	char	*err_target;
}	t_err_info;


int		handle_redirection(t_redirect *redir, t_in_out *in_out, t_context *ctx);
pid_t	exec_fork_pipe(t_cmd cmd, t_context *context, t_in_out *in_out);
pid_t	exec_fork_out(t_cmd cmd, t_context *context, t_in_out *in_out);
int		executer(t_cmd_line *cmd_line, t_context *context, t_in_out *in_out);
int		close_and_pipe(int in[2]);
void	set_in_out(int in[2], int out, t_in_out *in_out);
void	init_in_out(int in[2], int *out);
int		is_heredoc_str(char *s1, char *s2);
void	dup_errs(t_err_info *err_info, char *target, int status);
int		wait_all(pid_t *pids, size_t i, int ret);
int		exec_built_in(t_cmd cmd, t_context *context, t_isexit isexit);
void	exec_parenthesis(t_cmd *cmd, t_context *context, t_in_out *in_out);
void	check_cmd_type(t_cmd *cmd, t_context *context, \
											t_in_out *in_out, int *outpipe);

#endif