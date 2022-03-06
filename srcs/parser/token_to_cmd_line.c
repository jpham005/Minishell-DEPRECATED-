/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:52:28 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/07 04:26:25 by jaham            ###   ########.fr       */
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

int	is_pipe(char *s)
{
	if (s == NULL)
		return (0);
	if (!(ft_strncmp(s, "&&", 3)) || !(ft_strncmp(s, "||", 3)))
		return (1);
	return (0);
}

void	count_pipe(t_cmd_line *res, char **s)
{
	int	i;
	int	pipe_num;
	int	first;

	i = 0;
	pipe_num = 0;
	first = 1;
	while (s[i])
	{
		if (ft_strncmp(s[i], "|", 2) == 0)
			pipe_num++;
		if (is_pipe(s[i]))
		{
			if (first)
			{
				res->pipes->len = pipe_num + 1;
				first--;
			}
			else
				add_pipe(res, pipe_num + 1);
			pipe_num = 0;
		}
		i++;
	}
	if (first)
		res->pipes->len = pipe_num + 1;
	else
		add_pipe(res, pipe_num + 1);
}

t_token	*init_empty_token(void)
{
	t_token	*temp;

	temp = ft_calloc(sizeof(t_token), 1);
	temp->data = NULL;
	temp->next = NULL;
	return (temp);
}

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

int	is_par(char *str)
{
	if (!ft_strlen(str))
		return (0);
	if (str[0] == '(' && str[ft_strlen(str) - 1] == ')')
		return (1);
	return (0);
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
			j++;
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
		if (!fill_cmds(res, str))
		{
			free_c_dptr(&str);
			return (0);
		}
		free_c_dptr(&str);
		if (res->next)
			res = res->next;
		if (is_pipe(s[i]) && !s[i + 1])
			return (0);
		if (is_pipe(s[i]))
			res->pipes->type = check_pipe_type(s[i++]);
	}
	return (1);
}

int	is_redir2(char *s)
{
	return (
		!ft_strncmp(s, "<", 2)
		|| !ft_strncmp(s, ">", 2)
		|| !ft_strncmp(s, "<<", 3)
		|| !ft_strncmp(s, ">>", 3)
	);
}

int	fill_redir(t_cmd_line *res, t_redir_type type, char *target, int j)
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
					if (ft_strncmp(cp->pipes->cmds[j]->cmd[i], ">", 2) == 0)
						err = fill_redir(cp, REDIR_OUT, cp->pipes->cmds[j]->cmd[++i], j);
					else if (ft_strncmp(cp->pipes->cmds[j]->cmd[i], "<", 2) == 0)
						err = fill_redir(cp, REDIR_IN, cp->pipes->cmds[j]->cmd[++i], j);
					else if (ft_strncmp(cp->pipes->cmds[j]->cmd[i], "<<", 3) == 0)
						err = fill_redir(cp, REDIR_HEREDOC, cp->pipes->cmds[j]->cmd[++i], j);
					else if (ft_strncmp(cp->pipes->cmds[j]->cmd[i], ">>", 3) == 0)
						err = fill_redir(cp, REDIR_APPEND, cp->pipes->cmds[j]->cmd[++i], j);
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

void	delete_quote_2(char **str, int len, int i)
{
	char	*s;
	int		j;
	char	quote;

	s = ft_calloc(sizeof(char), len + 1);
	j = -1;
	quote = 0;
	len = 0;
	while (str[i][++j])
	{
		if (quote == 0 && (str[i][j] == '\'' || str[i][j] == '\"'))
		{
			quote = str[i][j];
			continue ;
		}
		else if ((quote == '\'' && str[i][j] == '\'') || (quote == '\"' && str[i][j] == '\"'))
		{
			quote = 0;
			continue ;
		}
		s[len++] = str[i][j];
	}
	s[len] = '\0';
	safe_free((void **) &str[i]);
	str[i] = ft_strdup(s);
	safe_free((void **) &s);
}

int	delete_quote_1(char **str)
{
	int	i;
	int	j;
	int	quote;
	int	len;

	i = -1;
	while (str[++i])
	{
		j = -1;
		quote = 0;
		len = 0;
		while (str[i][++j])
		{
			if (quote == 0 && (str[i][j] == '\'' || str[i][j] == '\"'))
			{
				quote = str[i][j];
				continue ;
			}
			else if ((quote == '\'' && str[i][j] == '\'') || (quote == '\"' && str[i][j] == '\"'))
			{
				quote = 0;
				continue ;
			}
			len++;
		}
		if (quote)
			return (0);
		delete_quote_2(str, len, i);
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
