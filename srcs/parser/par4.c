/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:18:18 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 21:50:27 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

char	*get_par4_value(t_context *ctx, char *e_v)
{
	char	*ret;

	ret = NULL;
	while (ctx->envp)
	{
		if (ft_strcmp(ctx->envp->key, e_v) == 0)
		{
			ret = ft_strdup(ctx->envp->value);
			break;
		}
		ctx->envp = ctx->envp->next;
	}
	return (ret);
}

// void	print_pars_s(char *pars_s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (*(pars_s + i) != NULL)
// 	{
// 		printf("%s\n", *(pars_s + i));
// 		i++;
// 	}
// }

char	*init_things(int len, int *i, int *j)
{
	char	*ret;

	ret = ft_malloc(sizeof(char), len + 1);
	*i = -1;
	*j = 0;
	return (ret);
}

void	swap_pars_s(char **pars_s_ss_i, char *ex_str)
{
	safe_free((void **) pars_s_ss_i);
	*pars_s_ss_i = ex_str;
}

// 환경변수가 확실히, 하나 있을 때만 처리할 수 있다.
// 여러 개일 때, ?일 때, 그저 문자일 뿐일 때를 구분하여 처리할 수 있어야 한다.
char	**par4(char **pars_s, char *e_v, int ss_i, t_context *ctx)
{
	int		i;
	int		j;
	int		len;
	char	*value;
	char	*ex_str;

	value = get_par4_value(ctx, e_v);
	// "$SHELL-123" --> /bin/bash-123
	len = ft_strlen(pars_s[ss_i]) - (1 + ft_strlen(e_v)) + ft_strlen(value);
	ex_str = init_things(len, &i, &j);
	if (ss_i != 0)
	{
		while (pars_s[ss_i][++i] != '$')
			ex_str[i] = pars_s[ss_i][i];
		if (value != NULL)
		{
			int idx = i + ft_strlen(e_v);
			while (value[j] != '\0')
				ex_str[i++] = value[j++];
			while (pars_s[ss_i][++idx] != '\0')
				ex_str[i++] = pars_s[ss_i][idx];
		}
		ex_str[i] = '\0';
		// printf("ex-str :: %s\n", ex_str);
		swap_pars_s(&pars_s[ss_i], ex_str);
	}
	// print_pars_s(pars_s);
	return (pars_s);
}
