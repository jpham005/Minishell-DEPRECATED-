/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:41:04 by jaham             #+#    #+#             */
/*   Updated: 2022/02/08 19:27:39 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_terminal.h"
#include "context.h"
#include "utils.h"

int	init_context(t_context *context, const char **envp)
{
	t_envp_list	*sh_envp;
	t_term		term;

	context->std_fd[0] = STDIN_FILENO;
	context->std_fd[1] = STDOUT_FILENO;
	context->std_fd[2] = STDERR_FILENO;
	if (tcgetattr(STDIN_FILENO, &term))
		return (print_error("tcgetattr: ", 0));
	context->exit_status = 0;
	context->default_term = term;
	term.c_lflag &= ~ECHOCTL;
	context->rl_term = term;
	if (!init_envp_list(&sh_envp, (const char **) envp))
		return (write_error(ENVP_ERR_MESSAGE, 0));
	context->envp = sh_envp;
	return (1);
}
