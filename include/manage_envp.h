/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_envp.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:20:39 by jaham             #+#    #+#             */
/*   Updated: 2022/02/03 21:21:38 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGE_ENVP_H
# define MANAGE_ENVP_H

# include <unistd.h>

typedef struct	s_envp_list
{
	char				*key;
	char				*value;
	size_t				list_len;
	struct s_envp_list	*next;
}	t_envp_list;

int		init_envp_list(t_envp_list **head, const char **envp);
int		clear_envp_list(t_envp_list **head);
void	del_one_envp_list(t_envp_list **head, char *key);
int		upadate_envp_list(t_envp_list **head, char *key, char *value);

#endif