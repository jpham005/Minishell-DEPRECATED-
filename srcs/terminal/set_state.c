/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:20:16 by jaham             #+#    #+#             */
/*   Updated: 2022/03/05 20:54:54 by jaham            ###   ########.fr       */
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
	tcsetattr(1, TCSANOW, &(term_state->rl_term));
}

static void	set_term_default(t_term_state *term_state)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	tcsetattr(1, TCSANOW, &(term_state->default_term));
}

char	*ft_readline(t_context *context, char *str)
{
	char	*ret;

	set_term_readline(&(context->term_state));
	if (!str)
		ret = readline(MINISHELL_WITH_COLOR);
	else
	{
		signal(SIGINT, heredoc_handler);
		ret = readline(str);
	}
	set_term_default(&(context->term_state));
	return (ret);
}
