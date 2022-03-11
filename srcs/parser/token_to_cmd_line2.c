/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_line2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:54:15 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/10 20:11:13 by jaham            ###   ########.fr       */
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

static void	fill_pipes_while(t_index *idx, char ***str, char **s)
{
	int	start;
	int	temp;

	idx->j = 0;
	start = idx->i;
	while (s[idx->i] && !(is_pipe(s[idx->i])))
		(idx->i)++;
	temp = idx->i - start + 1;
	*str = ft_calloc(sizeof(char *), temp);
	while (--temp)
		(*str)[(idx->j)++] = ft_strdup(s[start++]);
	(*str)[idx->j] = NULL;
}

int	fill_pipes(t_cmd_line *res, char **s)
{
	t_index	idx;
	char	**str;

	idx.i = 0;
	while (s[idx.i])
	{
		fill_pipes_while(&idx, &str, s);
		if (!fill_cmds(res, str))
		{
			free_c_dptr(&str);
			return (0);
		}
		free_c_dptr(&str);
		if (res->next)
			res = res->next;
		if (is_pipe(s[idx.i]) && !s[idx.i + 1])
			return (0);
		if (is_pipe(s[idx.i]))
			res->pipes->type = check_pipe_type(s[(idx.i)++]);
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
