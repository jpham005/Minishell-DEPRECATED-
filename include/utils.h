/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:46:28 by jaham             #+#    #+#             */
/*   Updated: 2022/02/13 13:53:33 by jaham            ###   ########.fr       */
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

# define ASCII_ART_PATH "imgs/"

#define END_TERM 1 << 0
#define ARG_ERR 1 << 1
#define DEFAULT_FD_ERR 1 << 2
#define PRINT_INTRO_ERR 1 << 3

int		exit_with_status(int status);
int		print_intro(void);

#endif