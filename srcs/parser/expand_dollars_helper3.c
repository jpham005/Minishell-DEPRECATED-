/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars_helper3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:59:02 by jaham             #+#    #+#             */
/*   Updated: 2022/03/07 18:14:15 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	expand_estat(char **ex_val, char **new, char **t_s, t_context *ctx)
{
	*ex_val = ft_itoa(ctx->exit_status);
	*new = ft_strjoin(*t_s, *ex_val);
	safe_free((void **) t_s);
	safe_free((void **) ex_val);
	*t_s = *new;
}

int	is_no_expand(char *str, t_index *idx, int *dollar_flag)
{
	return (
		(str[idx->i] != '$')
		|| ((str[idx->i] == '$') && (!dollar_flag[(idx->j)++]))
		|| ((str[idx->i] == '$') \
		&& ((!is_env_var(str[idx->i + 1]) || str[idx->i + 1] == '\0')))
	);
}

void	get_expand_val(int *i, char *str, t_context *context, char **ex_val)
{
	int	temp;

	temp = ++(*i);
	while (is_env_var(str[*i]) && str[*i] != '\0')
		(*i)++;
	*ex_val = is_envp(context, str, temp, *i);
}

void	get_new(char **ex_val, char **new, char **temp_s, int *i)
{
	if (*ex_val != NULL)
	{
		*new = ft_strjoin(*temp_s, *ex_val);
		safe_free((void **) temp_s);
		safe_free((void **) ex_val);
		*temp_s = *new;
	}
	else
		*new = *temp_s;
	(*i)--;
}
