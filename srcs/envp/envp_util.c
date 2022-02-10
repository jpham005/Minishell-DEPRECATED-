/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:48:09 by jaham             #+#    #+#             */
/*   Updated: 2022/02/10 14:56:06 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

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

char	**convert_envp_to_dptr(const t_envp_list *head)
{
	char	**ret;
	char	*temp;
	size_t	i;
	size_t	len;

	len = head->list_len;
	ret = ft_malloc(sizeof(char *), head->list_len + 1);
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
			return (free_c_dptr(&ret));
		head = head->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	sort_envp_dptr(char **envp)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	while (envp[i + 1])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[j]) + 1) > 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			j++;
		}
		i++;
	}
}

t_envp_list	*find_list_by_key(t_envp_list *head, const char *key)
{
	while (head && ft_strncmp(head->key, key, ft_strlen(key) + 1))
		head = head->next;
	if (!head)
		return (NULL);
	return (head);
}
