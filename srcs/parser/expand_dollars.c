/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:37:13 by jaham             #+#    #+#             */
/*   Updated: 2022/03/07 13:56:03 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static void	expand_estat(char **ex_val, char **new, char **t_s, t_context *ctx)
{
	*ex_val = ft_itoa(ctx->exit_status);
	*new = ft_strjoin(*t_s, *ex_val);
	safe_free((void **) t_s);
	safe_free((void **) ex_val);
	*t_s = *new;
}

static int	is_no_expand(char *str, int i, int j, int *dollar_flag)
{
	return (
		(str[i] != '$')
		|| ((str[i] == '$') && (!dollar_flag[j++]))
		|| ((str[i] == '$') \
						&& ((!is_env_var(str[i + 1]) || str[i + 1] == '\0')))
	);
}

static void	get_expand_val(int *i, char *str, t_context *context, char **ex_val)
{
	int	temp;

	temp = ++(*i);
	while (is_env_var(str[*i]) && str[*i] != '\0')
		(*i)++;
	*ex_val = is_envp(context, str, temp, *i);
}

static void	get_new(char **ex_val, char **new, char **temp_s, int *i)
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

void	change_dollar(t_context *ctx, int *dollar_flag, char *str, char **new)
{
	char	*temp_s;
	char	*expand_value;
	int		i;
	int		j;

	temp_s = NULL;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?' && dollar_flag[j])
		{
			expand_estat(&expand_value, new, &temp_s, ctx);
			i++;
			j++;
		}
		else if (is_no_expand(str, i, j, dollar_flag))
			ft_charjoin(new, &temp_s, str[i]);
		else
		{
			get_expand_val(&i, str, ctx, &expand_value);
			get_new(&expand_value, new, &temp_s, &i);
		}
		i++;
	}
	if (*new == NULL)
		*new = ft_strdup("");
}

void	expand_dollars(t_context *context, char **str)
{
	int		i;
	int		cnt;
	int		*dollar_flag;
	char	*new;

	i = -1;
	cnt = 0;
	dollar_flag = NULL;
	while (str[++i])
	{
		cnt = count_dollar(str[i]);
		if (cnt == 0)
			continue ;
		dollar_flag = ft_calloc(sizeof(int), cnt + 1);
		dollar_flag[cnt] = -2;
		check_dollar(dollar_flag, str[i]);
		change_dollar(context, dollar_flag, str[i], &new);
		safe_free((void **) &str[i]);
		str[i] = new;
		safe_free((void **) &dollar_flag);
	}
}
