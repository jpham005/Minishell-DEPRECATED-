/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_line_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:50:53 by jaham             #+#    #+#             */
/*   Updated: 2022/03/07 17:55:32 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

t_token	*init_empty_token(void)
{
	t_token	*temp;

	temp = ft_calloc(sizeof(t_token), 1);
	temp->data = NULL;
	temp->next = NULL;
	return (temp);
}

void	handle_zero_cnt(t_cmd_line *cp, int cnt, t_helper *idx)
{
	if (cnt == 0)
	{
		free_redir(cp->pipes->cmds[idx->j]->redir);
		cp->pipes->cmds[idx->j]->redir = NULL;
	}
}
