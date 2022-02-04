/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_manage.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:56:47 by jaham             #+#    #+#             */
/*   Updated: 2022/02/03 20:36:48 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_MANAGE_H
# define EXIT_MANAGE_H

# include <stdio.h>
# include <unistd.h>

# define PRT_INTRO_ERR_MESSAGE "Print Intro Error\n"
# define SET_TERM_ERR_MESSAGE "Setting Terminal Error\n"
# define EXEC_ERR_MESSAGE "Executing Error\n"
# define ARG_ERR_MESSAGE "Arg Error\n"
# define ENVP_ERR_MESSAGE "Envp init Error\n"

enum	e_exit_status
{
	SUCCESS = 0,
	FAIL = 1,
	PRT_INTRO_ERR = 0,
	SET_TERM_ERR,
	EXEC_ERR,
	END_TERM,
	ARG_ERR,
	ENVP_ERR
};

int	print_error(const char *str, int ret);
int	exit_with_status(int status);

#endif