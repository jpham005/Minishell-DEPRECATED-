/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars_helper3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:59:02 by jaham             #+#    #+#             */
/*   Updated: 2022/03/07 15:59:57 by jaham            ###   ########.fr       */
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

int	is_no_expand(char *str, int i, int j, int *dollar_flag)
{
	return (
		(str[i] != '$')
		|| ((str[i] == '$') && (!dollar_flag[j++]))
		|| ((str[i] == '$') \
						&& ((!is_env_var(str[i + 1]) || str[i + 1] == '\0')))
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
