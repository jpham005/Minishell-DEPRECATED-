/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:27:58 by jaham             #+#    #+#             */
/*   Updated: 2022/02/07 21:40:37 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include <termios.h>
# include "envp.h"

typedef struct termios	t_term;

typedef struct s_context
{
	int			std_fd[3];
	int			exit_status;
	t_term		default_term;
	t_term		rl_term;
	t_envp_list	*envp;
}	t_context;

int	init_context(t_context *context, const char **envp);

#endif