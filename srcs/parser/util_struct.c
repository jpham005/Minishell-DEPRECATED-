/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 02:42:28 by jaham             #+#    #+#             */
/*   Updated: 2022/03/10 21:16:02 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

t_token	*init_token(char *token)
{
	t_token	*res;

	res = ft_calloc(sizeof(t_token), 1);
	res->data = ft_strdup(token);
	res->next = NULL;
	return (res);
}

t_redirect	*init_redirect(t_redir_type type, char *target)
{
	t_redirect	*red;

	red = ft_calloc(sizeof(t_redirect), 1);
	red->type = type;
	red->target = ft_strdup(target);
	red->next = NULL;
	return (red);
}

void	add_pipe(t_cmd_line *res, int pipe_num)
{
	t_cmd_line	*new;

	new = init_cmd_line();
	new->pipes->len = pipe_num;
	while (res->next)
		res = res->next;
	res->next = new;
}

t_cmd_line	*init_cmd_line(void)
{
	t_cmd_line	*cml;

	cml = ft_calloc(sizeof(t_cmd_line), 1);
	cml->next = NULL;
	cml->pipes = ft_calloc(sizeof(t_pipe), 1);
	cml->pipes->len = 0;
	cml->pipes->type = PIPE;
	cml->pipes->cmds = NULL;
	return (cml);
}

void	add_token(t_token *token, char *data)
{
	t_token	*new;
	t_token	*cp;

	cp = token;
	if (!data)
		return ;
	if (token->data == NULL)
	{
		token->data = ft_strdup(data);
		return ;
	}
	while (cp->next)
		cp = cp->next;
	new = init_token(data);
	cp->next = new;
}
