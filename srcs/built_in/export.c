/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:44:39 by jaham             #+#    #+#             */
/*   Updated: 2022/02/12 19:32:14 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "envp.h"
#include "libft.h"

static int	check_valid(const char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*str && *str != '=')
	{
		if (!ft_isalpha(*str) && !ft_isnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

static void	exec_normal(t_envp_list *envp, size_t i, const char *str)
{
	char	*is_op;
	char	*key;
	char	*value;

	is_op = ft_strchr(str, '=');
	if (!is_op)
		return ;
	key = ft_substr(str, 0, ft_strlen(str) - ft_strlen(is_op));
	value = ft_substr(is_op, 1, ft_strlen(is_op) - 1);
	update_envp_list(&envp, key, value);
	safe_free((void **) &key);
	safe_free((void **) &value);
}

int	export(t_envp_list *envp, const char **argv)
{
	int		ret_flag;
	size_t	i;

	if (!argv)
	{
		print_envp(envp, SORT);
		return (0);
	}
	ret_flag = 0;
	i = 0;
	while (argv[i])
	{
		if (!check_valid(argv[i]))
		{
			printf(SHELL_NAME EXPORT_CMD"`%s': "EXPORT_ARG_ERR_MESSAGE, argv[i]);
			ret_flag |= 1;
		}
		else
			exec_normal(envp, i, argv[i]);
		i++;
	}
	return (ret_flag);
}
