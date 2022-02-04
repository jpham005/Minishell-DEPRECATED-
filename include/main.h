/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:47:53 by jaham             #+#    #+#             */
/*   Updated: 2022/02/03 12:45:36 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <termios.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "color.h"

# define MINISHELL_WITH_COLOR RED_BD"minishell "YELLOW_BT_BD"#"DEFAULT" "RED_BT
# define TOO_MANY_ARG_ERR_MESSAGE "Too many arg:\n"

int	set_term_default(void);

#endif