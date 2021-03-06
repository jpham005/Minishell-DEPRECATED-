/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:46:27 by jaham             #+#    #+#             */
/*   Updated: 2022/03/07 17:00:50 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

int	main(int argc, char **argv, char **envp)
{
	t_context	context;

	if (!check_arg(argc, (const char **) argv))
		exit_with_status(ARG_ERR, &context);
	if (!check_tty(0, 1, 2))
		exit_with_status(DEFAULT_FD_ERR, &context);
	init_shell(&context, (const char **) envp);
	if (!print_intro())
		exit_with_status(PRINT_INTRO_ERR, &context);
	readline_loop(&context);
	return (context.exit_status);
}
