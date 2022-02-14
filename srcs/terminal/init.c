/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:41:04 by jaham             #+#    #+#             */
/*   Updated: 2022/02/14 21:04:37 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "utils.h"
#include "envp.h"
#include "libft.h"

void	init_shell(t_context *context, t_term_state *t_state, const char **envp)
{
	t_term		term;
	t_envp_list	*shlvl;

	context->std_fd[0] = STDIN_FILENO;
	context->std_fd[1] = STDOUT_FILENO;
	context->std_fd[2] = STDERR_FILENO;
	if (tcgetattr(STDOUT_FILENO, &term))
		perror_exit("tcgetattr", 1);
	context->exit_status = 0;
	t_state->default_term = term;
	term.c_lflag &= ~ECHOCTL;
	t_state->rl_term = term;
	init_envp_list(&(context->envp), (const char **) envp);
	shlvl = find_list_by_key(context->envp, "SHLVL");
	update_envp_list(&(context->envp), "SHLVL", shlvl->value + 1);
}
