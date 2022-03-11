/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_line4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:38:00 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/10 21:33:26 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

void	init_cmds_and_redir(t_cmd_line *res)
{
	size_t	i;

	i = 0;
	res->pipes->cmds = ft_calloc(sizeof(t_cmd *), res->pipes->len);
	while (i < res->pipes->len)
	{
		res->pipes->cmds[i] = ft_calloc(sizeof(t_cmd), 1);
		i++;
	}
	i = 0;
	while (i < res->pipes->len)
	{
		res->pipes->cmds[i]->redir = ft_calloc(sizeof(t_redirect), 1);
		res->pipes->cmds[i]->redir->target = NULL;
		res->pipes->cmds[i]->redir->next = NULL;
		i++;
	}
}

void	remove_par(char **str, int idx, t_cmd_line *res, int cmds_num)
{
	int		i;
	int		j;
	int		end;
	char	*ret;

	i = -1;
	j = 0;
	end = ft_strlen(str[idx]) - 1;
	ret = ft_calloc(sizeof(char), end);
	while (str[idx][++i])
	{
		if (i == 0 || i == end)
			continue ;
		ret[j] = str[idx][i];
		j++;
	}
	ret[j] = '\0';
	safe_free((void **) &str[idx]);
	str[idx] = ft_strdup(ret);
	safe_free((void **) &ret);
	res->pipes->cmds[cmds_num]->type = PARENTHESIS;
}

int	fill_r(t_cmd_line *res, t_redir_type type, char *target, int j)
{
	t_redirect	*new;
	t_redirect	*temp;

	if (target == NULL || is_redir2(target))
		return (1);
	if (res->pipes->cmds[j]->redir->target == NULL)
	{
		res->pipes->cmds[j]->redir->type = type;
		res->pipes->cmds[j]->redir->target = ft_strdup(target);
	}
	else
	{
		temp = res->pipes->cmds[j]->redir;
		new = init_redirect(type, target);
		while (res->pipes->cmds[j]->redir->next)
			res->pipes->cmds[j]->redir = res->pipes->cmds[j]->redir->next;
		res->pipes->cmds[j]->redir->next = new;
		res->pipes->cmds[j]->redir = temp;
	}
	return (0);
}

int	is_redir(char *s, int *i)
{
	if (!s)
		return (0);
	if (
		!ft_strncmp(s, "<", 2)
		|| !ft_strncmp(s, ">", 2)
		|| !ft_strncmp(s, "<<", 3)
		|| !ft_strncmp(s, ">>", 3)
	)
	{
		(*i)++;
		return (1);
	}
	return (0);
}
