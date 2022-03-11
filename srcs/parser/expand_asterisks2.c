/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:17:57 by hyeonpar          #+#    #+#             */
/*   Updated: 2022/03/07 14:23:36 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>

int	find_char(char *str, char s)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == s)
			return (i);
		i++;
	}
	return (-1);
}

void	check_side(char **list, char *arg)
{
	int	i;

	i = -1;
	while (list[++i] != NULL)
	{
		if (
			((arg[0] == '*') || ((arg[0] != '*') && (list[i][0] == arg[0])))
			&& ((arg[ft_strlen(arg) - 1] == '*') \
			|| ((arg[ft_strlen(arg) - 1] != '*') \
			&& (list[i][ft_strlen(list[i]) - 1] == arg[ft_strlen(arg) - 1])))
			)
			continue ;
		else
		{
			safe_free((void **) &list[i]);
			list[i] = ft_strdup(" ");
		}
	}
}

char	**current_path_ls(void)
{
	DIR				*dp;
	struct dirent	*dirp;
	int				i;
	char			*arr[256];
	char			**res;

	dp = opendir(".");
	i = 0;
	while (1)
	{
		dirp = readdir(dp);
		if (dirp == NULL)
			break ;
		if (dirp->d_name[0] != '.')
		{
			arr[i++] = ft_strdup(dirp->d_name);
		}
	}
	res = (char **)ft_calloc(sizeof(char *), i + 1);
	*(res + i) = NULL;
	while (--i > -1)
		*(res + i) = arr[i];
	closedir(dp);
	return (res);
}

char	*del_quote_2(char *arg, char *no_q)
{
	int		i;
	int		len;
	char	quote;

	i = -1;
	len = 0;
	quote = 0;
	while (arg[++i] != '\0')
	{
		if (quote == 0 && (arg[i] == '\'' || arg[i] == '\"'))
		{
			quote = arg[i];
			continue ;
		}
		else if (quote != 0 && quote == arg[i])
		{
			quote = 0;
			continue ;
		}
		no_q[len] = arg[i];
		len++;
	}
	no_q[len] = '\0';
	return (no_q);
}

char	*del_quote(char *arg)
{
	int		i;
	int		len;
	char	quote;
	char	*no_q;

	i = -1;
	len = 0;
	quote = 0;
	while (arg[++i] != '\0')
	{
		if (quote == 0 && (arg[i] == '\'' || arg[i] == '\"'))
		{
			quote = arg[i];
			continue ;
		}
		else if (quote != 0 && quote == arg[i])
		{
			quote = 0;
			continue ;
		}
		len++;
	}
	no_q = ft_calloc(sizeof(char), len + 1);
	return (del_quote_2(arg, no_q));
}
