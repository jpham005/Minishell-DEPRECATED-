/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:41:42 by jaham             #+#    #+#             */
/*   Updated: 2022/02/14 21:43:31 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "terminal.h"

int	cd(t_context *context, const char **argv)
{
	t_envp_list	*home;

	if (!argv[1])
	{
		home = find_list_by_key(context->envp, "HOME");
		if (!home || )
		{
			ft_putstr_fd(HOME_NOT_SET_ERR_MESSAGE, 2);
			return (1);
		}
	}
}

/*
no arg => $HOME
additional arg => ignore
CDPATH => test path
success CDPATH, - => write(1, "path")
cd ../srcs
cd =>go to home
cd ..
cd ../
cd - : display oldpwd+\n, move to oldpwd
oldpwd
pwd
*/