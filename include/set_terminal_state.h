/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal_state.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:20:54 by jaham             #+#    #+#             */
/*   Updated: 2022/02/02 17:18:15 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_TERMINAL_STATE_H
# define SET_TERMINAL_STATE_H

# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SIG_QUIT_MESSAGE "Quit: 3\n"

int		set_term_default(void);
int		set_term_execute(void);
void	sig_int_handler_default(int sig);

#endif