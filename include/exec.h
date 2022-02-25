/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:45:13 by jaham             #+#    #+#             */
/*   Updated: 2022/02/25 17:36:41 by jaham            ###   ########.fr       */
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

void			executor(t_cmd_line *c_line, t_context *ctx, t_in_out *in_out);
int				exec_built_in(char **cmd, t_context *ctx, t_sh_built_in type);
int				handle_redir(t_redir *redir, t_context *context);
t_sh_built_in	is_built_in(char *cmd);

#endif