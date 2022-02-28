/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:21:18 by jaham             #+#    #+#             */
/*   Updated: 2022/02/28 17:34:06 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "libft.h"
#include <stdio.h>

static void	print_envp_export(t_envp_list *head)
{
	char	**temp;
	size_t	i;

	temp = convert_envp_to_dptr(head);
	sort_envp_dptr(temp);
	i = 0;
	while (temp[i])
	{
		printf("declare -x %s\n", temp[i]);
		i++;
	}
}

static void	print_envp_env(t_envp_list *head)
{
	while (head)
	{
		if (head->value[0] != '\0')
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}

void	print_envp(t_envp_list *head, int op)
{
	if (op & SORT)
		print_envp_export(head);
	else
		print_envp_env(head);
}
