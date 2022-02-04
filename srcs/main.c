/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:46:27 by jaham             #+#    #+#             */
/*   Updated: 2022/02/04 13:57:48 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "set_terminal_state.h"
#include "print_intro.h"
#include "exit_manage.h"
#include "manage_envp.h"
#include "convert_exit_status.h"
#include "libft.h"

//parser part
static int	parse(const char *str)
{
	int	pid;
	int	status;

	if (!ft_strncmp("loop", str, 5))
	{
		pid = fork();
		if (!pid)
			execve("jaham_test/loop", NULL, NULL);
		else
			waitpid(pid, &status, 0);
	}
	return (123);
}
//

static int	check_arg(int argc, const char **argv)
{
	int	i;

	i = 1;
	if (argc != 1)
	{
		ft_putstr_fd(TOO_MANY_ARG_ERR_MESSAGE, 2);
		while (argv[i])
		{
			ft_putstr_fd(argv[i++], 2);
			ft_putstr_fd("\n", 2);
		}
		return (0);
	}
	return (1);
}

static int	readline_loop(t_envp_list *sh_envp)
{
	char	*str;
	char	*exit_status;

	while (1)
	{
		str = readline(MINISHELL_WITH_COLOR);
		if (!str)
			return (exit_with_status(END_TERM));
		set_term_execute();
		exit_status = exit_status_to_a(parse(str)); // parser here
		if (!exit_status)
			return (exit_with_status(EXEC_ERR));
		if (!upadate_envp_list(&sh_envp, "exit_status", exit_status))
			return (exit_with_status(EXEC_ERR));
		safe_free((void **) &exit_status);
		signal(SIGINT, sig_int_handler_default);
		signal(SIGQUIT, SIG_IGN);
		safe_free((void **) &str);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_envp_list	*sh_envp;

	if (!check_arg(argc, (const char **) argv))
		return (exit_with_status(ARG_ERR));
	if (!init_envp_list(&sh_envp, (const char **) envp))
		return (exit_with_status(ENVP_ERR));
	if (!upadate_envp_list(&sh_envp, "exit_status", "0"))
	{
		clear_envp_list(&sh_envp);
		return (exit_with_status(ENVP_ERR));
	}
	if (!print_intro())
		return (exit_with_status(PRT_INTRO_ERR));
	if (!set_term_default())
		return (exit_with_status(SET_TERM_ERR));
	if (readline_loop(sh_envp))
		return (exit_with_status(EXEC_ERR));
	clear_envp_list(&sh_envp);
	return (SUCCESS);
}
