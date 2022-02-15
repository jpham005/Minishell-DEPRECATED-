/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:41:42 by jaham             #+#    #+#             */
/*   Updated: 2022/02/15 17:06:07 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "terminal.h"

int	test_path(const char *path_value, const char *str)
{
	char	**path;

	path = ft_split(path_value, ':');
}

int	move_by_home(t_context *context)
{
	t_envp_list	*home;

	home = find_list_by_key(context->envp, "HOME");
	if (!home)
	{
		ft_putstr_fd(HOME_NOT_SET_ERR_MESSAGE, 2);
		return (1);
	}

}

int	cd(t_context *context, const char **argv)
{
	t_envp_list	*home;

	if (!argv[1])
		move_by_home(context);
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
Not a directory
bash: cd: asdf: Permission denied
*/