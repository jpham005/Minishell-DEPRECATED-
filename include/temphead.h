/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temphead.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:49:29 by jaham             #+#    #+#             */
/*   Updated: 2022/02/18 21:14:10 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPHEAD_H
# define TEMPHEAD_H

typedef struct s_redire
{
	int				type; // >, >>, <, <<
	char			*str; // NULL when stdio
	struct s_redire *next;
}	t_redir;

typedef struct s_cmd
{
	char	**cmd; // execve(cmd[0], cmd, envp);
	t_redir	*in; // <, <<, NULL if default
	t_redir	*out; // > >>, NULL if default
}	t_cmd;

typedef struct s_parse
{
	t_cmd cmd;
	int		type; // default : pipe    &&, ||
}	t_parse;

typedef strcut

#endif