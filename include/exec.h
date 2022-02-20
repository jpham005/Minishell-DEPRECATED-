/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:45:13 by jaham             #+#    #+#             */
/*   Updated: 2022/02/20 17:40:55 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "envp.h"
#include "temphead.h"

typedef struct s_out
{
	int	outpipe[2];
	int out;
}	t_out;

int		is_built_in(const char *cmd);
int		handle_redirection(t_redirect *redir, int in[2], int *out);
pid_t	exec_fork_pipe(int in[2], int *out, t_cmd cmd, t_envp_list *envp);

#endif