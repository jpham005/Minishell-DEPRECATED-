/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:52:28 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/07 17:22:40 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

t_token	*init_empty_token(void)
{
	t_token	*temp;

	temp = ft_calloc(sizeof(t_token), 1);
	temp->data = NULL;
	temp->next = NULL;
	return (temp);
}

int	fill_cmd_redir(t_cmd_line *res)
{
	t_token		*temp;
	t_cmd_line	*cp;
	int			i;
	size_t		j;
	int			cnt;
	int			err;

	cp = res;
	while (cp)
	{
		j = -1;
		while (++j < cp->pipes->len)
		{
			temp = init_empty_token();
			i = 0;
			cnt = 0;
			while (cp->pipes->cmds[j]->cmd[i])
			{
				if (is_redir(cp->pipes->cmds[j]->cmd[i], &cnt))
				{
					if
					(ft_strncmp(cp->pipes->cmds[j]->cmd[i], ">", 2) == 0)
						err = fill_r(cp, 2, cp->pipes->cmds[j]->cmd[++i], j);
					else if
					(ft_strncmp(cp->pipes->cmds[j]->cmd[i], "<", 2) == 0)
						err = fill_r(cp, 0, cp->pipes->cmds[j]->cmd[++i], j);
					else if
					(ft_strncmp(cp->pipes->cmds[j]->cmd[i], "<<", 3) == 0)
						err = fill_r(cp, 1, cp->pipes->cmds[j]->cmd[++i], j);
					else if
					(ft_strncmp(cp->pipes->cmds[j]->cmd[i], ">>", 3) == 0)
						err = fill_r(cp, 3, cp->pipes->cmds[j]->cmd[++i], j);
					if (err)
						return (0);
				}
				else
					add_token(temp, cp->pipes->cmds[j]->cmd[i]);
				if (cp->pipes->cmds[j]->cmd[i] != NULL)
					i++;
			}
			if (cnt == 0)
			{
				free_redir(cp->pipes->cmds[j]->redir);
				cp->pipes->cmds[j]->redir = NULL;
			}
			free_c_dptr(&cp->pipes->cmds[j]->cmd);
			cp->pipes->cmds[j]->cmd = convert_token_to_dptr(temp);
			free_token(temp);
		}
		cp = cp->next;
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
