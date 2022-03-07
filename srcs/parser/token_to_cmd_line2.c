/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_line2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:54:15 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/07 15:23:52 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

t_pipe_type	check_pipe_type(char *s)
{
	if (ft_strncmp(s, "&&", 3) == 0)
		return (AND);
	if (ft_strncmp(s, "||", 3) == 0)
		return (OR);
	else
		return (PIPE);
}

void	fill_cmds_helper(t_cmd_line *res, char **str)
{
	if (!fill_cmds(res, str))
	{
		free_c_dptr(&str);
		return (0);
	}
	free_c_dptr(&str);
	if (res->next)
		res = res->next;
}

int	fill_pipes(t_cmd_line *res, char **s)
{
	int		i;
	int		j;
	int		start;
	int		temp;
	char	**str;

	i = 0;
	while (s[i])
	{
		j = 0;
		start = i;
		while (s[i] && !(is_pipe(s[i])))
			i++;
		temp = i - start + 1;
		str = ft_calloc(sizeof(char *), temp);
		while (--temp)
			str[j++] = ft_strdup(s[start++]);
		str[j] = NULL;
		fill_cmds_helper(res, str);
		if (is_pipe(s[i]) && !s[i + 1])
			return (0);
		if (is_pipe(s[i]))
			res->pipes->type = check_pipe_type(s[i++]);
	}
	return (1);
}

void	count_pipe(t_cmd_line *res, char **s)
{
	int	i;
	int	pipe_num;
	int	first;

	i = -1;
	pipe_num = 0;
	first = 1;
	while (s[++i])
	{
		if (ft_strncmp(s[i], "|", 2) == 0)
			pipe_num++;
		if (is_pipe(s[i]) && first)
		{
			res->pipes->len = pipe_num + 1;
			first--;
		}
		else if (is_pipe(s[i]) && !first)
			add_pipe(res, pipe_num + 1);
		if (is_pipe(s[i]))
			pipe_num = 0;
	}
	if (first)
		res->pipes->len = pipe_num + 1;
	else
		add_pipe(res, pipe_num + 1);
}
