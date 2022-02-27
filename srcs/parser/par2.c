/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 06:20:29 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/02/27 07:50:37 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>

// t_token		*make_token(t_token *res, char *s)
// {
// }

// t_cmd_line	*make_cmd(char *str)
// {
// 	t_token *res;

// 	res = init_token();
// 	res = make_token(res, str);

// }


char	**convert_token_to_dptr(t_token *head)
{
	char	**ret;
	t_token	*cp;
	size_t	i;
	size_t	len;

	cp = head;
	len = 0;
	while (cp)
	{
		len++;
		cp = cp->next;
	}
	ret = ft_malloc(sizeof(char *), len + 1);
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