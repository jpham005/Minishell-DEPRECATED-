/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:20:16 by jaham             #+#    #+#             */
/*   Updated: 2022/02/08 16:37:52 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_terminal.h"
#include "utils.h"
#include "context.h"
#include "color.h"

void	set_term_default(t_context *context)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	context->rl_term = term;
	signal(SIGINT, sig_int_handler_default);
	signal(SIGQUIT, SIG_IGN);
}

void	set_term_readline(t_context *context)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_handler_exec);
	tcsetattr(STDIN_FILENO, TCSANOW, &(context->rl_term));
}

void	set_term_default(t_context *context)
{
	signal(SIGQUIT, sig_quit_handler);
	signal(SIGINT, sig_int_handler_default);
	tcsetattr(STDIN_FILENO, TCSANOW, &(context->default_term));
}

char	*ft_readline(t_context *context)
{
	char	*ret;

	set_term_readline(context);
	ret = readline(MINISHELL_WITH_COLOR);
	tcsetattr(STDIN_FILENO, TCSANOW, &(context->default_term));
}
