/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:45:13 by jaham             #+#    #+#             */
/*   Updated: 2022/02/21 02:39:01 by jaham            ###   ########.fr       */
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

int		is_built_in(const char *cmd);
int		handle_redirection(t_redirect *redir, t_in_out *in_out);
pid_t	exec_fork_pipe(t_cmd cmd, t_context *context, t_in_out *in_out);
pid_t	exec_fork_out(t_cmd cmd, t_context *context, t_in_out *in_out);
int		executer(t_cmd_line *cmd_line, t_context *context);

#endif