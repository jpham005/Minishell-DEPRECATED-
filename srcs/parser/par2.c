/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 06:20:29 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/06 03:46:39 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>

t_token	*convert_dptr_to_struct(char **tokens)
{
	t_token *res;
	int i;
	int first;

	i = 0;
	first = 1;
	while (tokens[i])
	{
		if (!ft_is_space(tokens[i][0]))
		{
			if (first)
			{
				res = init_token(tokens[i]);
				first = 0;
			}
			else
				add_token(res, tokens[i]);
		}
		i++;
	}
	return (res);
}

char	**convert_token_to_dptr(t_token *head)
{
	char	**ret;
	t_token	*cp;
	size_t	i;
	size_t	len;

	cp = head;
	len = 0;
	if (cp->data == NULL)
		return (NULL);
	while (cp)
	{
		len++;
		cp = cp->next;
	}
	ret = ft_malloc(sizeof(char *), len + 1);
//printf("par2 ret %p\n", ret);
	i = 0;
	while (i < len)
	{
		ret[i] = ft_strdup(head->data);
		i++;
		head = head->next;
	}
	ret[i] = NULL;

	return (ret);
}