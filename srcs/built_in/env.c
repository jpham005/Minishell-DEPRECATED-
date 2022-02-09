/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 21:51:24 by jaham             #+#    #+#             */
/*   Updated: 2022/02/09 21:27:14 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "context.h"
#include "libft.h"

static int	print_envp(t_envp_list *head)
{
	while (head)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return (0);
}

int	copy_envp()

int	add_to_envp(t_context *context, const char *str)
{
	char	*key;
	char	*value;
	char	*sep;
	size_t	key_len;
	int		ret;

	sep = ft_strchr(str, '=');
	key_len = ft_strlen(str) - ft_strlen(sep);
	key = ft_substr(str, 0, key_len);
	value = ft_substr(str, key_len + 1, ft_strlen(sep) - 1);
	if (!key || !value)
		ret = 0;
	else if (!upadate_envp_list(&(context->envp), key, value))
		ret = 0;
	else
		ret = 1;
	safe_free((void **) &key);
	safe_free((void **) &value);
	return (ret);
}

int	env(t_context *context, const char **argv)
{
	size_t	i;
	char	*key;
	char	*value;

	i = 0;
	if (!argv)
		return (print_envp(context->envp));
	if (copy_envp(context, ))
	while (argv[i])
	{
		if (!ft_strchr(argv[i], '='))
			return (execve_path(argv + i, context->envp)); // pass to executer (built_in || execve)
		if (!add_to_envp(context, argv[i]))
			return (1);
		i++;
	}
	return (0);
}

/*
env prog= true # runs 'true', with prog= in environment
env ./prog= true # runs 'true', with ./prog= in environment
env -- prog= true # runs 'true', with prog= in environment
env # print envp
env non_key # execve(cmd)
doesnt check valid key=value (everything is fine)
*/