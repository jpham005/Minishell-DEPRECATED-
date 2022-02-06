/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:50:38 by jaham             #+#    #+#             */
/*   Updated: 2022/02/06 19:29:24 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include <unistd.h>
# include "libft.h"

typedef struct s_envp_list
{
	char				*key;
	char				*value;
	size_t				list_len;
	struct s_envp_list	*next;
}	t_envp_list;

int			init_envp_list(t_envp_list **head, const char **envp);
int			clear_envp_list(t_envp_list **head);
void		del_one_envp_list(t_envp_list **head, char *key);
int			upadate_envp_list(t_envp_list **head, char *key, char *value);
int			get_key(t_envp_list *curr, const char *envp);
int			get_value(t_envp_list *curr, const char *envp);
char		**convert_envp_to_dptr(const t_envp_list *head);
t_envp_list	*find_list_by_key(t_envp_list *head, const char *key);

#endif