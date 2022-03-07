/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_line5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:45:32 by jaham             #+#    #+#             */
/*   Updated: 2022/03/07 16:45:45 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int	is_redir2(char *s)
{
	return (
		!ft_strncmp(s, "<", 2)
		|| !ft_strncmp(s, ">", 2)
		|| !ft_strncmp(s, "<<", 3)
		|| !ft_strncmp(s, ">>", 3)
	);
}

int	is_par(char *str)
{
	if (!ft_strlen(str))
		return (0);
	if (str[0] == '(' && str[ft_strlen(str) - 1] == ')')
		return (1);
	return (0);
}

int	is_pipe(char *s)
{
	if (s == NULL)
		return (0);
	if (!(ft_strncmp(s, "&&", 3)) || !(ft_strncmp(s, "||", 3)))
		return (1);
	return (0);
}
