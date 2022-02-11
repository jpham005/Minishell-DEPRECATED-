/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 21:51:24 by jaham             #+#    #+#             */
/*   Updated: 2022/02/11 21:28:17 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"

void	add_to_envp(t_envp_list *head, const char *str)
{
	char	*key;
	char	*value;
	char	*sep;
	size_t	key_len;

	sep = ft_strchr(str, '=');
	key_len = ft_strlen(str) - ft_strlen(sep);
	key = ft_substr(str, 0, key_len);
	value = ft_substr(str, key_len + 1, ft_strlen(sep) - 1);
	upadate_envp_list(&head, key, value);
	print_envp(head, UNSORT);
	safe_free((void **) &key);
	safe_free((void **) &value);
}

int	env(t_envp_list *envp, const char **argv)
{
	t_envp_list	*cp;
	size_t		i;
	char		*key;
	char		*value;
	int			ret;

	if (!argv)
	{
		print_envp(envp, UNSORT);
		return (0);
	}
	cp = copy_envp_list(envp);
	i = 0;
	while (argv[i])
	{
		if (!ft_strchr(argv[i], '='))
		{
			// ret = execve_path(argv + i, cp);
			clear_envp_list(&cp);
			return (ret);
		}// pass to executer (built_in || execve) return exit_status
		add_to_envp(cp, argv[i++]);
	}
	// print_envp(cp, UNSORT);
	return (clear_envp_list(&cp));
}

/*
env prog= true # runs 'true', with prog= in environment
env ./prog= true # runs 'true', with ./prog= in environment
env -- prog= true # runs 'true', with prog= in environment
env # print envp
env non_key # execve(cmd)
doesnt check valid key=value (everything is fine)
*/