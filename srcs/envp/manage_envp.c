/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:20:24 by jaham             #+#    #+#             */
/*   Updated: 2022/02/07 15:55:55 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"
#include "utils.h"

void	del_one_envp_list(t_envp_list **head, const char *key)
{
	t_envp_list	*temp;
	t_envp_list	*cp;

	cp = *head;
	while (*head && ft_strncmp((*head)->key, key, ft_strlen(key) + 1))
		head = &((*head)->next);
	if (*head)
	{
		temp = *head;
		*head = (*head)->next;
		safe_free((void **) &(temp->key));
		safe_free((void **) &(temp->value));
		safe_free((void **) &temp);
		cp->list_len--;
	}
}

int	upadate_envp_list(t_envp_list **head, char *key, char *value)
{
	t_envp_list	*new;
	t_envp_list	*cp;

	cp = *head;
	while (*head && ft_strncmp((*head)->key, key, ft_strlen(key) + 1))
		head = &((*head)->next);
	if (*head)
	{
		safe_free((void **) &((*head)->value));
		(*head)->value = ft_strdup(value);
		if (!((*head)->value))
			return (0);
		return (1);
	}
	new = ft_malloc(sizeof(t_envp_list), 1);
	if (!new)
		return (0);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	*head = new;
	cp->list_len++;
	return (1);
}

int	clear_envp_list(t_envp_list **head)
{
	t_envp_list	*cp;
	t_envp_list	*temp;

	cp = *head;
	while (cp)
	{
		safe_free((void **) &(cp->key));
		safe_free((void **) &(cp->value));
		temp = cp->next;
		safe_free((void **) &cp);
		cp = temp;
	}
	*head = NULL;
	return (0);
}

int	init_envp_list(t_envp_list **head, const char **envp)
{
	t_envp_list	**cp;
	size_t		cnt;

	cp = head;
	cnt = 0;
	while (envp[cnt])
	{
		*head = ft_malloc(sizeof(t_envp_list), 1);
		if (!*head)
			return (clear_envp_list(head));
		(*head)->next = NULL;
		if (!get_key(*head, envp[cnt]))
			return (clear_envp_list(head));
		if (!get_value(*head, envp[cnt]))
		{
			safe_free((void **) &((*head)->key));
			return (clear_envp_list(head));
		}
		head = &((*head)->next);
		cnt++;
	}
	*head = NULL;
	(*cp)->list_len = cnt;
	return (1);
}
