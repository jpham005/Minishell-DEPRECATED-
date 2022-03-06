/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:09:03 by jaham             #+#    #+#             */
/*   Updated: 2022/03/06 13:10:11 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

t_cmd_line	*parse(t_context *context, const char *str)
{
	t_cmd_line *cml;
	char **t;
	char **s;
	t_token *a;

	t = tokenizer(str);
	if (!t)
		return (NULL);
	a = convert_dptr_to_struct(t);
	s = convert_token_to_dptr(a);

	expand_dollars(context, s);
	expand_asterisks(s);

	cml = token_to_cmd_line(s);
    print_struct(cml);
	free_token(a);
	free_c_dptr(&s);
	free_c_dptr(&t);
	return (cml);
}
