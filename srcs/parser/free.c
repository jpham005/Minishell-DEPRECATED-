/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 00:33:02 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/05 01:10:24 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	free_token(t_token *token)
{
	t_token *temp;

	while (token)
	{
		temp = token;
		token = token->next;
		safe_free((void **) &temp->data);
		safe_free((void **) &temp);
	}
}

void	free_redir(t_redirect *redir)
{
	t_redirect *temp;

	while (redir)
	{
		temp = redir;
		redir = redir->next;
		if (temp->target != NULL)
			safe_free((void **) &redir->target);
		safe_free((void **) &temp);
	}
}

void	free_cmd_line(t_cmd_line *cml)
{
	t_cmd_line *temp;
	int i;

	while (cml)
	{
		i = 0;
		while (i < cml->pipes->num)
		{
			free_redir(cml->pipes->cmds[i]->redir);
			safe_free((void **) cml->pipes->cmds[i]->cmd);
			i++;
		}
		safe_free((void **) cml->pipes->cmds);

		temp = cml;
		cml = cml->next;
		safe_free((void **) &temp->pipes);
		safe_free((void **) &temp);
	}
}