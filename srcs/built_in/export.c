/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:44:39 by jaham             #+#    #+#             */
/*   Updated: 2022/02/06 20:33:01 by jaham            ###   ########.fr       */
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

static int	check_valid(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '#');
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
	char	*key;
	char	*value;
	int		ret_flag;
	size_t	i;

	if (!str)
		return (print_envp(head, 0));
	ret_flag = 0;
	i = 0;
	while (str[i])
	{
		if (!check_valid(str[i][0]))
		{
			printf("export: `%s': not a valid identifier\n", str[i]);
			ret_flag |= 1;
		}
		else
		{
			if (!exec_normal(head, i, str[i]))
				ret_flag |= 1;
		}
		if (str[i][0] == '#')
			break ;
		i++;
	}
	char temp[2];
	temp[1] = 0;
	temp[0] = ret_flag + '0';
	upadate_envp_list(&head, "exit_status", temp);
	return (ret_flag);
}
