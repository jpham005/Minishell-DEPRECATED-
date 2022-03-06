/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precheck_syntax_err.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:44:52 by jaham             #+#    #+#             */
/*   Updated: 2022/03/07 02:20:57 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	handle_syntax_err(t_context *context)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(SYNTAX_ERR_MESSAGE, 2);
	context->exit_status = 258;
}

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
	return (
		str[0] != '|'
		&& str[ft_strlen(str) - 1] != '|'
		&& !ft_strnstr(str, "|||", ft_strlen(str))
	);
}

int	check_syntax_err(char **str, t_context *context)
{
	char	*trimed_str;

	trimed_str = ft_strtrim(*str, " \t\n");
	if (!check_logical_err(trimed_str) || !check_pipe_err(trimed_str))
	{
		safe_free((void **) str);
		safe_free((void **) &trimed_str);
		handle_syntax_err(context);
		return (0);
	}
	safe_free((void **) &trimed_str);
	return (1);
}
