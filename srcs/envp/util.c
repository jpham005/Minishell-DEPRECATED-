/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:08:27 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 18:03:58 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "libft.h"

void	get_key(t_envp_list *curr, const char *envp)
{
	size_t	key_len;

	key_len = 0;
	while (envp[key_len] && envp[key_len] != '=')
		key_len++;
	curr->key = ft_substr(envp, 0, key_len);
}

void	get_value(t_envp_list *curr, const char *envp)
{
	size_t	value_len;
	size_t	start;

	value_len = ft_strlen(envp) - ft_strlen(curr->key) - 1;
	start = ft_strlen(curr->key) + 1;
	curr->value = ft_substr(envp, start, value_len);
}
