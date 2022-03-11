/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:52:28 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/10 21:30:42 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

static int	fill_handle_redir(t_cmd_line *cp, t_helper *helper)
{
	while (is_redir(cp->pipes->cmds[helper->j]->cmd[helper->i], &helper->cnt))
	{
		if (ft_strncmp(cp->pipes->cmds[helper->j]->cmd[helper->i], ">", 2) == 0)
			helper->err = \
				fill_r(cp, 2, cp->pipes->cmds[helper->j]->cmd[++(helper->i)], \
																	helper->j);
		else if
		(ft_strncmp(cp->pipes->cmds[helper->j]->cmd[helper->i], "<", 2) == 0)
			helper->err = \
				fill_r(cp, 0, cp->pipes->cmds[helper->j]->cmd[++(helper->i)], \
																	helper->j);
		else if
		(ft_strncmp(cp->pipes->cmds[helper->j]->cmd[helper->i], "<<", 3) == 0)
			helper->err = \
				fill_r(cp, 1, cp->pipes->cmds[helper->j]->cmd[++(helper->i)], \
																	helper->j);
		else if
		(ft_strncmp(cp->pipes->cmds[helper->j]->cmd[helper->i], ">>", 3) == 0)
			helper->err = \
				fill_r(cp, 3, cp->pipes->cmds[helper->j]->cmd[++(helper->i)], \
																	helper->j);
		if (helper->err == 0)
			helper->i++;
	}
	return (helper->err <= 0);
}

static int	fill_cmd_redir_while(t_cmd_line *cp, \
												t_helper *helper, t_token *temp)
{
	while (cp->pipes->cmds[helper->j]->cmd[helper->i])
	{
		if (!fill_handle_redir(cp, helper))
			return (0);
		else
			add_token(temp, cp->pipes->cmds[helper->j]->cmd[helper->i]);
		if (cp->pipes->cmds[helper->j]->cmd[helper->i] != NULL)
			(helper->i) += 1;
	}
	return (1);
}

int	fill_cmd_redir(t_cmd_line *res)
{
	t_token		*temp;
	t_helper	helper;

	helper.err = -1;
	while (res)
	{
		helper.j = -1;
		while (++(helper.j) < (int) res->pipes->len)
		{
			temp = init_empty_token();
			helper.i = 0;
			helper.cnt = 0;
			if (!fill_cmd_redir_while(res, &helper, temp))
				return (0);
			handle_zero_cnt(res, helper.cnt, &helper);
			free_c_dptr(&res->pipes->cmds[helper.j]->cmd);
			res->pipes->cmds[helper.j]->cmd = convert_token_to_dptr(temp);
			free_token(temp);
		}
		res = res->next;
	}
	return (1);
}

t_cmd_line	*token_to_cmd_line(char **s)
{
	t_cmd_line	*res;

	if (!delete_quote_1(s))
		return (NULL);
	res = init_cmd_line();
	count_pipe(res, s);
	if (!fill_pipes(res, s))
	{
		free_cmd_line_e(res);
		return (NULL);
	}
	if (!fill_cmd_redir(res))
	{
		free_cmd_line_e(res);
		return (NULL);
	}
	return (res);
}
