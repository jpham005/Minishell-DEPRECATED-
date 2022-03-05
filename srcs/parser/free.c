/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 00:33:02 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/06 03:08:24 by hyeonpar         ###   ########.fr       */
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
			safe_free((void **) &temp->target);
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
			free_c_dptr(&cml->pipes->cmds[i]->cmd);
			i++;
		}
		safe_free((void **) cml->pipes->cmds);

		temp = cml;
		cml = cml->next;
		safe_free((void **) &temp->pipes);
		safe_free((void **) &temp);
	}
}

void	free_cmd_line_e(t_cmd_line *cml)
{
	t_cmd_line *temp;
	int i;

	while (cml)
	{
		i = 0;
		while (i < cml->pipes->num)
		{
			// 임시 처리, leak 잡아야 함 (cmds 항상 발생, cmd, redir)
			if (i != cml->pipes->num - 1)
			{
				free_c_dptr(&cml->pipes->cmds[i]->cmd);
				free_redir(cml->pipes->cmds[i]->redir);
			}
			//
			i++;
		}
		safe_free((void **) cml->pipes->cmds); //

		temp = cml;
		cml = cml->next;
		safe_free((void **) &temp->pipes);
		safe_free((void **) &temp);
	}
}