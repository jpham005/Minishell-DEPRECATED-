/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_line3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:00:32 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/07 15:37:03 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

int	is_redir2(char *s)
{
	return (
		!ft_strncmp(s, "<", 2)
		|| !ft_strncmp(s, ">", 2)
		|| !ft_strncmp(s, "<<", 3)
		|| !ft_strncmp(s, ">>", 3)
	);
}

int	is_par(char *str)
{
	if (!ft_strlen(str))
		return (0);
	if (str[0] == '(' && str[ft_strlen(str) - 1] == ')')
		return (1);
	return (0);
}

int	is_pipe(char *s)
{
	if (s == NULL)
		return (0);
	if (!(ft_strncmp(s, "&&", 3)) || !(ft_strncmp(s, "||", 3)))
		return (1);
	return (0);
}

int	fill_cmds(t_cmd_line *res, char **str)
{
	t_token	*temp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	temp = init_empty_token();
	init_cmds_and_redir(res);
	while (str[++i])
	{
		if (is_par(str[i]))
			remove_par(str, i, res, j);
		if (ft_strncmp(str[i], "|", 2) == 0)
		{
			res->pipes->cmds[j]->cmd = convert_token_to_dptr(temp);
			if (res->pipes->cmds[j]->type != PARENTHESIS)
				res->pipes->cmds[j]->type = SINGLE_CMD;
			if (!temp->data)
			{
				free_token(temp);
				return (0);
			}
			free_token(temp);
			temp = init_empty_token();
		}
		else
			add_token(temp, str[i]);
	}
	if (!temp->data)
	{
		free_token(temp);
		return (0);
	}
	res->pipes->cmds[j]->cmd = convert_token_to_dptr(temp);
	free_token(temp);
	if (res->pipes->cmds[j]->type != PARENTHESIS)
		res->pipes->cmds[j]->type = SINGLE_CMD;
	return (1);
}
