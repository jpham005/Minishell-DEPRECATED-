/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_line3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:00:32 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/07 16:59:01 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

static void	fill_cmds_check_cmd_type(t_cmd_line *res, int j)
{
	if (res->pipes->cmds[j]->type != PARENTHESIS)
		res->pipes->cmds[j]->type = SINGLE_CMD;
}

static int	cmds_is_p(t_cmd_line *res, t_index *idx, t_token **temp)
{
	res->pipes->cmds[idx->j]->cmd = convert_token_to_dptr(*temp);
	fill_cmds_check_cmd_type(res, idx->j);
	if (!(*temp)->data)
	{
		free_token(*temp);
		*temp = NULL;
		return (0);
	}
	free_token(*temp);
	*temp = init_empty_token();
	(idx->j)++;
	return (1);
}

static void	init_idx_fill_cmds(t_index *idx)
{
	idx->i = -1;
	idx->j = 0;
}

static int	fill_cmds_last(t_cmd_line *res, t_token **temp, t_index *idx)
{
	res->pipes->cmds[idx->j]->cmd = convert_token_to_dptr(*temp);
	free_token(*temp);
	*temp = NULL;
	fill_cmds_check_cmd_type(res, idx->j);
	return (1);
}

int	fill_cmds(t_cmd_line *res, char **str)
{
	t_token	*temp;
	t_index	idx;

	init_idx_fill_cmds(&idx);
	temp = init_empty_token();
	init_cmds_and_redir(res);
	while (str[++(idx.i)])
	{
		if (is_par(str[idx.i]))
			remove_par(str, idx.i, res, idx.j);
		if (ft_strncmp(str[idx.i], "|", 2) == 0)
		{
			if (!cmds_is_p(res, &idx, &temp))
				return (0);
		}
		else
			add_token(temp, str[idx.i]);
	}
	if (!temp->data)
	{
		free_token(temp);
		return (0);
	}
	return (fill_cmds_last(res, &temp, &idx));
}
