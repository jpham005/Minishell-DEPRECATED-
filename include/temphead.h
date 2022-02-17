/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temphead.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:49:29 by jaham             #+#    #+#             */
/*   Updated: 2022/02/17 19:56:14 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPHEAD_H
# define TEMPHEAD_H

typedef struct s_command
{
	char	**cmd;
	int		in;
	int		out;
	int		pipe[2];
	int		type;
}	t_command;

#endif