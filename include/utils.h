/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:46:28 by jaham             #+#    #+#             */
/*   Updated: 2022/02/11 15:12:57 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

# define PRT_INTRO_ERR_MESSAGE "Print Intro Error\n"
# define SET_TERM_ERR_MESSAGE "Setting Terminal Error\n"
# define ARG_ERR_MESSAGE "Arg Error\n"
# define DEFAULT_FD_ERR_MESSAGE "Default fd Error\n"
# define INIT_CONTEXT_ERR_MESSAGE "Init context Error\n"

# define ASCII_ART_PATH "imgs/"

enum	e_exit_status
{
	SUCCESS = 0,
	PRT_INTRO_ERR = 0,
	END_TERM,
	ARG_ERR,
	DEFAULT_FD_ERR,
	INIT_CONTEXT_ERR
};

int		print_error(const char *str, int ret);
int		write_error(const char *str, int ret);
int		exit_with_status(int status);
int		print_intro(void);

#endif