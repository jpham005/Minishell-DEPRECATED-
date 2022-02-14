/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:44:39 by jaham             #+#    #+#             */
/*   Updated: 2022/02/14 15:27:30 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "envp.h"
#include "libft.h"
#include "terminal.h"

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

int	export(t_context *context, const char **argv)
{
	int		ret_flag;
	size_t	i;

	if (!argv[1])
	{
		print_envp(context->envp, SORT);
		return (0);
	}
	ret_flag = 0;
	i = 1;
	while (argv[i])
	{
		if (!check_valid(argv[i]))
		{
			printf(SHELL_NAME EXPORT_CMD"`%s': "EXPORT_ARG_ERR_MESSAGE, argv[i]);
			ret_flag |= 1;
		}
		else
			exec_normal(context->envp, i, argv[i]);
		i++;
	}
	return (ret_flag);
}
