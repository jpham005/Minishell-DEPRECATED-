/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:54:45 by jaham             #+#    #+#             */
/*   Updated: 2022/03/06 04:11:08 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "exec.h"
#include "libft.h"
#include "parser.h"
#include "terminal.h"
#include "utils.h"

#include <sys/wait.h> // temp
#include <stdlib.h>
#include <stdio.h>
//parser part
t_cmd_line	*parse(t_context *context, const char *str, int *result)
{
	t_cmd_line *cml;
	char **t;
	char **s;
	t_token *a;

	t = tokenizer(str);
	// int i = 0;
    // while (t[i])
    // {
    //     printf("%s\n", t[i++]);
    // }
	if (!t)
	{
		printf("괄호 열림\n");
		return (NULL);
	}
	a = convert_dptr_to_struct(t);
	s = convert_token_to_dptr(a);

	expand_dollars(context, s);
	expand_asterisks(context, s);

	cml = token_to_cmd_line(s);
    print_struct(cml);

	// free
	free_token(a);
	free_c_dptr(&s);
	free_c_dptr(&t);
	
	//  echo a > b | c > d || cat -e
	// leak cmds, cmd만 남음

	return (cml);
}

int	readline_loop(t_context *context)
{
	char		*str;
	t_cmd_line	*cmd_line;

	while (1)
	{
		str = ft_readline(context, NULL);
		if (!str)
			exit(exit_with_status(END_TERM));
		if (!check_valid_str(str, context))
		{
			safe_free((void **) &str);
			continue ;
		}
		cmd_line = parse(context, str, NULL);
		safe_free((void **) &str);
		if (!cmd_line)
		{
			printf("parse error\n");
			continue ;
		}
		executor(cmd_line, context, NULL);
		// fprintf(stdout, "exit status %d\n", context->exit_status);
		free_cmd_line(cmd_line);
	}
	return (0);
}
