/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:45:13 by jaham             #+#    #+#             */
/*   Updated: 2022/02/19 21:12:08 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef enum e_built_in
{
	CD = 0,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET,
	NONE
}	t_built_in;

typedef enum e_pipe_type // will use hyeonpar's
{
	PIPE = 0,
	AND,
	OR
}	t_pipe_type;

int		is_built_in(const char *cmd);
int		handle_inpipe(int in[2], t_redirect *redir, int type, char *target);

#endif