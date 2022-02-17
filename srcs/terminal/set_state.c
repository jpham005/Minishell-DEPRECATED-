/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:20:16 by jaham             #+#    #+#             */
/*   Updated: 2022/02/14 21:04:50 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "utils.h"
#include "color.h"

void	set_term_readline(t_term_state *term_state)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_handler_default);
	tcsetattr(STDOUT_FILENO, TCSANOW, &(term_state->rl_term));
}

void	set_term_default(t_term_state *term_state)
{
	signal(SIGQUIT, sig_quit_handler);
	signal(SIGINT, sig_int_handler_exec);
	tcsetattr(STDOUT_FILENO, TCSANOW, &(term_state->default_term));
}

char	*ft_readline(t_term_state *term_state)
{
	char	*ret;

	set_term_readline(term_state);
	ret = readline(MINISHELL_WITH_COLOR);
	set_term_default(term_state);
	return (ret);
}