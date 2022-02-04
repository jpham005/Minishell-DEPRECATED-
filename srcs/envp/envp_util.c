/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:48:09 by jaham             #+#    #+#             */
/*   Updated: 2022/02/04 11:10:22 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp_util.h"
#include "libft.h"

int	get_key(t_envp_list *curr, const char *envp)
{
	size_t	key_len;
	size_t	i;

	key_len = 0;
	while (envp[key_len] && envp[key_len] != '=')
		key_len++;
	curr->key = ft_substr(envp, 0, key_len);
	if (!(curr->key))
		return (0);
	return (1);
}

int	get_value(t_envp_list *curr, const char *envp)
{
	size_t	value_len;
	size_t	i;
	size_t	start;

	value_len = ft_strlen(envp) - ft_strlen(curr->key) - 1;
	start = ft_strlen(curr->key) + 1;
	curr->value = ft_substr(envp, start, value_len);
	if (!(curr->value))
		return (0);
	return (1);
}

char	**convert_to_dptr(const t_envp_list *head)
{
	char	**ret;
	char	*temp;
	size_t	i;
	size_t	len;

	len = head->list_len;
	ret = malloc(sizeof(char *) * (head->list_len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = ft_strjoin(head->key, "=");
		temp = ret[i];
		ret[i] = ft_strjoin(ret[i], head->value);
		safe_free((void **) &temp);
		if (!ret[i])
		{
			while (i--)
				safe_free((void **) &ret[i]);
			return (NULL);
		}
		head = head->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

// WIP : find node by key, get_PATH (ft_split?)