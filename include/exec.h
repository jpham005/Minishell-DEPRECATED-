/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:45:13 by jaham             #+#    #+#             */
/*   Updated: 2022/02/21 20:51:21 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "envp.h"
#include "temphead.h"
#include "terminal.h"

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

int		is_built_in(const char *cmd);
int		handle_redirection(t_redirect *redir, t_in_out *in_out, t_context *ctx);
pid_t	exec_fork_pipe(t_cmd cmd, t_context *context, t_in_out *in_out);
pid_t	exec_fork_out(t_cmd cmd, t_context *context, t_in_out *in_out);
int		executer(t_cmd_line *cmd_line, t_context *context);
int		close_and_pipe(int in[2]);
void	set_in_out(int in[2], int out, t_in_out *in_out);
void	init_in_out(int in[2], int *out);
int		is_heredoc_str(char *s1, char *s2);
void	dup_errs(t_err_info *err_info, char *target, int status);

#endif