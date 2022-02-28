/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:20:16 by jaham             #+#    #+#             */
/*   Updated: 2022/02/28 18:08:58 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "terminal.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>

static void	set_term_readline(t_term_state *term_state)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_handler_readline);
	tcsetattr(STDOUT_FILENO, TCSANOW, &(term_state->rl_term));
}

static void	set_term_default(t_term_state *term_state)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	tcsetattr(STDOUT_FILENO, TCSANOW, &(term_state->default_term));
}

static void	heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		exit(2);
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
