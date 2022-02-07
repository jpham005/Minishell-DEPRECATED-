/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:44:39 by jaham             #+#    #+#             */
/*   Updated: 2022/02/07 15:32:28 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "envp.h"
#include "libft.h"

static int	print_envp(const t_envp_list *head, int ret)
{
	while (head)
	{
		printf("declare -x %s=\"%s\"\n", head->key, head->value);
		head = head->next;
	}
	return (ret);
}

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

static int	exec_normal(t_envp_list *head, size_t i, const char *str)
{
	char	*is_op;
	char	*key;
	char	*value;
	int		ret;

	if (*str == '#' && i == 0)
		return (print_envp(head, 1));
	is_op = ft_strchr(str, '=');
	if (!is_op)
		return (1);
	key = ft_substr(str, 0, ft_strlen(str) - ft_strlen(is_op));
	value = ft_substr(is_op, 1, ft_strlen(is_op) - 1);
	if (key && value)
		ret = upadate_envp_list(&head, key, value);
	else
		ret = 0;
	safe_free((void **) &key);
	safe_free((void **) &value);
	return (ret);
}

int	export(t_envp_list *head, const char **str)
{
	int		ret_flag;
	size_t	i;

	if (!str)
		return (print_envp(head, 0));
	ret_flag = 0;
	i = 0;
	while (str[i])
	{
		if (!check_valid(str[i]))
		{
			printf(SHELL_NAME EXPORT_CMD"`%s': "EXPORT_ARG_ERR_MESSAGE, str[i]);
			ret_flag |= 1;
		}
		else
		{
			if (!exec_normal(head, i, str[i]))
				ret_flag |= 1;
		}
		if (str[i++][0] == '#')
			break ;
	}
	return (ret_flag);
}
