/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:20:16 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 19:09:53 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>

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

void	heredoc(int sig)
{
	if (sig == SIGINT)
		exit(2);
}

void	heredoc_parent_handler(int sig)
{
	if (sig == SIGINT)
	{
		return ;
	}
}

char	*ft_readline(t_context *context, char *str)
{
	char	*ret;

	set_term_readline(&(context->term_state));
	if (!str)
		ret = readline(MINISHELL_WITH_COLOR);
	else
	{
		signal(SIGINT, heredoc);
		ret = readline(str);
	}
	set_term_default(&(context->term_state));
	return (ret);
}
