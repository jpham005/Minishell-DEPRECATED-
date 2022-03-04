/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:41:04 by jaham             #+#    #+#             */
/*   Updated: 2022/03/04 15:42:30 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "terminal.h"

void	init_shell(t_context *context, const char **envp)
{
	t_term		term;
	t_envp_list	*shlvl;

	context->std_fd[0] = ft_dup(STDIN_FILENO);
	context->std_fd[1] = ft_dup(STDOUT_FILENO);
	context->std_fd[2] = ft_dup(STDERR_FILENO);
	if (tcgetattr(STDOUT_FILENO, &term))
		perror_exit("tcgetattr", 1);
	context->exit_status = 0;
	context->term_state.default_term = term;
	term.c_lflag &= ~ECHOCTL;
	context->term_state.rl_term = term;
	init_envp_list(&(context->envp), (const char **) envp);
	shlvl = find_list_by_key(context->envp, "SHLVL");
	update_envp_list(&(context->envp), "SHLVL", shlvl->value + 1);
}
