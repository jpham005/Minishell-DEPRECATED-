/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:21:18 by jaham             #+#    #+#             */
/*   Updated: 2022/02/17 15:33:07 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include <stdio.h>

void	print_envp_sort(t_envp_list *head)
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

void	print_envp_unsort(t_envp_list *head)
{
	while (head)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}

void	print_envp(t_envp_list *head, int op)
{
	if (op & SORT)
		print_envp_sort(head);
	else
		print_envp_unsort(head);
}
