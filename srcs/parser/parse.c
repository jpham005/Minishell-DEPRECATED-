/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:09:03 by jaham             #+#    #+#             */
/*   Updated: 2022/03/06 19:22:03 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int is_pipe_or_and(char *s)
{
	return (!ft_strncmp(s, "|", 2) || !ft_strncmp(s, "||", 3) || !ft_strncmp(s, "&&", 3));
}

int	valid_par(char **list)
{
	int i;
	int par_idx;

	i = 0;
	par_idx = -2;
	while (list[i])
	{
		if (i - 1 == par_idx)
		{
			if (!is_pipe_or_and(list[i]))
				return (0);
		}
		if (is_par(list[i]))
			par_idx = i;
		if (is_par(list[i + 1]))
		{
			par_idx = i + 1;
			if (!is_pipe_or_and(list[i]))
				return (0);
		}
		i++;
	}
	return (1);
}

t_cmd_line	*parse(t_context *context, const char *str)
{
	t_cmd_line *cml;
	char **t;
	char **s;
	t_token *a;

	t = tokenizer(str);
	if (!t)
	{
		free_c_dptr(&t);
		return (NULL);
	}
	a = convert_dptr_to_struct(t);
	free_c_dptr(&t);
	s = convert_token_to_dptr(a);
	free_token(a);
	if (!valid_par(s))
	{
		free_c_dptr(&s);
		return (NULL);
	}
	expand_dollars(context, s);
	expand_asterisks(s);
	cml = token_to_cmd_line(s);
    // print_struct(cml);
	free_c_dptr(&s);
	return (cml);
}
