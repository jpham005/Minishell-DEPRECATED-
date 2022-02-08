/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:34:09 by jaham             #+#    #+#             */
/*   Updated: 2022/02/08 20:03:09 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "envp.h"
#include "libft.h"

static int	check_valid(const char *key)
{
	if (!ft_isalpha(*key) && *key != '_')
		return (0);
	while (*key)
	{
		if (!ft_isalpha(*key) && !ft_isnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

int	unset(t_envp_list *head, const char **str)
{
	int		ret_flag;
	size_t	i;

	if (!str)
		return (0);
	ret_flag = 0;
	i = 0;
	while (str[i])
	{
		if (!check_valid(str[i]))
		{
			printf(SHELL_NAME UNSET_CMD"`%s': "UNSET_ARG_ERR_MESSAGE, str[i]);
			ret_flag |= 1;
		}
		else
			del_one_envp_list(&head, str[i]);
		i++;
	}
	return (ret_flag);
}
