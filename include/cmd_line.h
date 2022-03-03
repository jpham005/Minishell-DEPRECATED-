/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:16:53 by jaham             #+#    #+#             */
/*   Updated: 2022/03/04 01:21:47 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LINE_H
# define CMD_LINE_H

# include <unistd.h>

typedef enum e_cmd_type
{
	SINGLE_CMD = 0,
	PARENTHESIS
}	t_cmd_type;

typedef enum e_pipe_type
{
	PIPE = 0,
	AND,
	OR
}	t_pipe_type;

typedef enum e_redir_type
{
	REDIR_IN = 0,
	REDIR_HEREDOC,
	REDIR_OUT,
	REDIR_APPEND
}	t_redir_type;

typedef struct s_redirect
{
	t_redir_type		type;
	char				*target;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	char		**cmd;
	t_redirect	*redir;
	t_cmd_type	type;
}	t_cmd;

typedef struct s_pipe
{
	t_cmd		**cmds;
	size_t		len;
	t_pipe_type	type;
}	t_pipe;

typedef struct s_cmd_line
{
	t_pipe				*pipes;
	struct s_cmd_line	*next;
}	t_cmd_line;

#endif