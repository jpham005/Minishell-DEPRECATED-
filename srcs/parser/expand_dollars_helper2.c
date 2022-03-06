/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars_helper2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 03:27:29 by jaham             #+#    #+#             */
/*   Updated: 2022/03/07 04:25:14 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

char	*is_envp(t_context *context, char *str, int start, int end)
{	
	int			i;
	int			len;
	char		*s;
	char		*ret;
	t_envp_list	*cp;

	cp = context->envp;
	i = 0;
	len = end - start;
	ret = NULL;
	s = ft_calloc(sizeof(char), len + 1);
	while (i < len)
		s[i++] = str[start++];
	s[i] = '\0';
	while (cp)
	{
		if (ft_strcmp(cp->key, s) == 0)
		{
			ret = ft_strdup(cp->value);
			break ;
		}
		cp = cp->next;
	}
	safe_free((void **) &s);
	return (ret);
}

void	ft_charjoin(char **new, char **temp_s, char c)
{
	int		i;
	char	*ret;
	size_t	s1_len;

	if (!(*temp_s))
	{
		ret = ft_calloc(sizeof(char), 2);
		ret[0] = c;
		ret[1] = '\0';
	}
	else
	{
		i = -1;
		s1_len = ft_strlen((*temp_s));
		ret = ft_calloc(sizeof(char), s1_len + 1 + 1);
		while ((*temp_s)[++i])
			ret[i] = (*temp_s)[i];
		ret[i] = c;
		ret[i + 1] = '\0';
	}
	*new = ret;
	safe_free((void **) temp_s);
	*temp_s = *new;
}
