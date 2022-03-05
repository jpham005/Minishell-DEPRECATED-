/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:37:13 by jaham             #+#    #+#             */
/*   Updated: 2022/03/06 03:46:32 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

int	is_valid_dollar(char *str, int end)
{
	int i;
	int	quote;

	i = 0;
	quote = 0;
	while (i < end)
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		i++;
	}
	if (quote == '\'')
		return (0);
	return (1);
}

void check_dollar(int *dollar_flag, char *str)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			dollar_flag[j++] = is_valid_dollar(str, i);
	}
}

int		count_dollar(char *s)
{
	int i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == '$')
			cnt++;
		i++;
	}
	return (cnt);
}

char	*is_envp(t_context *context, char *str, int start, int end)
{	
	int i;
	int len;
	char *s;
	char *ret;

	i = 0;
	len = end - start;
	ret = NULL;
	s = ft_malloc(sizeof(char), len + 1);
//printf("isenvp s: %p\n", s);
	while (i < len)
		s[i++] = str[start++];
	s[i] = '\0';
	while (context->envp)
	{
		if (ft_strcmp(context->envp->key, s) == 0)
		{
			ret = ft_strdup(context->envp->value);
			break;
		}
		context->envp = context->envp->next;
	}
	safe_free((void **) &s);
	return (ret);
}

char	*ft_charjoin(char *s1, char c)
{
	int		i;
	char	*ret;
	size_t	s1_len;

	if (!s1)
	{
		ret = ft_malloc(sizeof(char), 2);
//printf("char join ret1 %p\n", ret);
		ret[0] = c;
		ret[1] = '\0';
		return (ret);
	}
	i = -1;
	s1_len = ft_strlen(s1);
	ret = ft_malloc(sizeof(char), s1_len + 1 + 1);
//printf("char join ret2 %p\n", ret);
	while (s1[++i])
		ret[i] = s1[i];
	ret[i] = c;
	ret[i + 1] = '\0';
	return (ret);
}

int	is_env_var(char c)
{
	if ((ft_isalpha(c) || ft_isdigit(c) || c == '_'))
		return (1);
	return (0);
}

char	*change_dollar(t_context *context, int *dollar_flag, char *str)
{
	char *new;
	char *temp_s;
	char *expand_value;
	int i;
	int j;
	int temp;

	temp_s = NULL;
	i = 0;
	j = 0;
	temp = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?' && dollar_flag[j])
		{
			expand_value = ft_itoa(context->exit_status);
			new = ft_strjoin(temp_s, expand_value);
			safe_free((void **) &temp_s);
			safe_free((void **) &expand_value);
			temp_s = new;
			i++;
			j++;
		}
		else if (
			(str[i] != '$') 
			|| ((str[i] == '$') && (!dollar_flag[j++])) 
			|| ((str[i] == '$') && ((!is_env_var(str[i + 1]) || str[i + 1] == '\0')))
			)
		{
			new = ft_charjoin(temp_s, str[i]);
			safe_free((void **) &temp_s);
			temp_s = new;
		}
		else
		{
			temp = ++i;
			while (is_env_var(str[i]) && str[i] != '\0')
				i++;
			expand_value = is_envp(context, str, temp, i);
			if (expand_value != NULL)
			{
				new = ft_strjoin(temp_s, expand_value);
				safe_free((void **) &temp_s);
				safe_free((void **) &expand_value);
				temp_s = new;
			}
			i--;
		}
		i++;
	}
	if (new == NULL)
		new = ft_strdup("");
	return (new);
}

void	expand_dollars(t_context *context, char **str)
{
	int	i;
	int cnt;
	int *dollar_flag;
	char *new;
	
	i = -1;
	cnt = 0;
	dollar_flag = NULL;
	while (str[++i])
	{
		cnt = count_dollar(str[i]);
		if (cnt == 0)
			continue ;
		dollar_flag = ft_malloc(sizeof(int), cnt + 1);
//printf("dollar_flag %p\n", dollar_flag);
		dollar_flag[cnt] = -2;
		check_dollar(dollar_flag, str[i]);
		new = change_dollar(context, dollar_flag, str[i]);
		safe_free((void **) &str[i]);
		str[i] = new;
		safe_free((void **) &dollar_flag);
	}
}