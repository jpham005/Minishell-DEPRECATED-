/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precheck_syntax_err.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:44:52 by jaham             #+#    #+#             */
/*   Updated: 2022/03/07 17:08:35 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static int	check_logical_err(char *str)
{
	return (
		ft_strncmp(str, "&&", 2)
		&& ft_strncmp(str + ft_strlen(str) - 2, "&&", 2)
		&& ft_strncmp(str, "||", 2)
		&& ft_strncmp(str + ft_strlen(str) - 2, "||", 2)
	);
}

static int	check_pipe_err(char *str)
{
	char	**splited;
	size_t	i;

	splited = ft_split(str, " \t\n");
	i = 0;
	while (splited[i + 1])
	{
		if (
			splited[i][ft_strlen(splited[i]) - 1] == '|'
			&& splited[i + 1][0] == '|'
		)
		{
			free_c_dptr(&splited);
			return (0);
		}
		i++;
	}
	free_c_dptr(&splited);
	return (
		str[0] != '|'
		&& str[ft_strlen(str) - 1] != '|'
		&& !ft_strnstr(str, "|||", ft_strlen(str))
	);
}

static int	check_parenthesis_err(char *str)
{
	size_t	i;
	int		parenthesis;

	i = 0;
	parenthesis = 0;
	while (str[i])
	{
		if (str[i] == '(')
			parenthesis++;
		else if (str[i] == ')')
			parenthesis--;
		if (parenthesis < 0)
			return (0);
		i++;
	}
	return (!parenthesis);
}

static int	check_redir_err(char *str)
{
	return (
		str[ft_strlen(str) - 1] != '<'
		&& str[ft_strlen(str) - 1] != '>'
	);
}

int	check_syntax_err(char **str, t_context *context)
{
	char	*trimed_str;

	trimed_str = ft_strtrim(*str, " \t\n");
	if (
		!check_logical_err(trimed_str)
		|| !check_pipe_err(trimed_str)
		|| !check_parenthesis_err(trimed_str)
		|| !check_redir_err(trimed_str)
	)
	{
		safe_free((void **) str);
		safe_free((void **) &trimed_str);
		handle_syntax_err(context);
		return (0);
	}
	safe_free((void **) &trimed_str);
	return (1);
}
