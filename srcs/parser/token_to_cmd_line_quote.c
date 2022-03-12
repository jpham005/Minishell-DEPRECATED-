/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_line_quote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:12:15 by jaham             #+#    #+#             */
/*   Updated: 2022/03/12 17:25:40 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static void	delete_quote_2_while(char **str, int *len, t_index *idx, char *s)
{
	int	quote;

	quote = 0;
	while (str[idx->i][++(idx->j)])
	{
		if (quote == 0 && (str[idx->i][idx->j] == '\'' \
											|| str[idx->i][idx->j] == '\"'))
		{
			quote = str[idx->i][idx->j];
			continue ;
		}
		else if ((quote == '\'' && str[idx->i][idx->j] == '\'') ||
		(quote == '\"' && str[idx->i][idx->j] == '\"'))
		{
			quote = 0;
			continue ;
		}
		s[(*len)++] = str[idx->i][idx->j];
	}
}

void	delete_quote_2(char **str, int len, int i)
{
	char	*s;
	char	quote;
	t_index	idx;

	s = ft_calloc(sizeof(char), len + 1);
	idx.j = -1;
	idx.i = i;
	quote = 0;
	len = 0;
	delete_quote_2_while(str, &len, &idx, s);
	s[len] = '\0';
	safe_free((void **) &str[idx.i]);
	str[idx.i] = ft_strdup(s);
	safe_free((void **) &s);
}

static void	delete_qoute_1_while(char **str, t_index *idx, int *quote, int *len)
{
	while (str[idx->i][++(idx->j)])
	{
		if (*quote == 0 && (str[idx->i][idx->j] == '\'' \
											|| str[idx->i][idx->j] == '\"'))
		{
			*quote = str[idx->i][idx->j];
			continue ;
		}
		else if ((*quote == '\'' && str[idx->i][idx->j] == '\'') ||
		(*quote == '\"' && str[idx->i][idx->j] == '\"'))
		{
			*quote = 0;
			continue ;
		}
		(*len)++;
	}
}

int	delete_quote_1(char **str)
{
	t_index	idx;
	int		quote;
	int		len;

	idx.i = -1;
	while (str[++(idx.i)])
	{
		idx.j = -1;
		quote = 0;
		len = 0;
		delete_qoute_1_while(str, &idx, &quote, &len);
		if (quote)
			return (0);
		delete_quote_2(str, len, idx.i);
	}
	return (1);
}
