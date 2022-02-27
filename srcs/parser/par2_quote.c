/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par2_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:37:13 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 18:05:22 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	del_q(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = str[i + 1];
		i++;
	}
}

void	check_flag(char **pars_str, int *flag_q, int *flag_qq, size_t i)
{
	if (pars_str[i][0] == '\'')
	{
		del_q(pars_str[i]); // 'err\0 --> err\0\0 || err'\0 --> err\0\0
		*flag_q = 1;
	}
	else if (pars_str[i][0] == '\"')
	{
		del_q(pars_str[i]);
		*flag_qq = 1;
	}
}

char **par2(char **pars_str, char **envp, t_context *context)
{
	size_t	i;
	int		flag_q;
	int		flag_qq;

	i = 0;
	flag_q = 0;
	flag_qq = 0;
	/* del q */
	while (*(pars_str + i) != NULL)
	{
		check_flag(pars_str, &flag_q, &flag_qq, i);
		if (pars_str[i + 1] == NULL && (flag_q || flag_qq))
		{
			int j = 0;
			while (pars_str[i][j] != '\0')
			{
				if (pars_str[i][j + 1] == '\0')
					pars_str[i][j] = '\0';
				j++;
			}
		}
		i++;
	}
	return (par3(pars_str, envp, flag_q, context));
}
