/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:50:38 by jaham             #+#    #+#             */
/*   Updated: 2022/02/17 15:32:37 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include <unistd.h>

# define SORT 1 << 0
# define UNSORT 1 << 1

typedef struct s_envp_list
{
	char				*key;
	char				*value;
	size_t				list_len;
	struct s_envp_list	*next;
}	t_envp_list;

int			init_envp_list(t_envp_list **head, const char **envp);
int			clear_envp_list(t_envp_list **head);
void		del_one_envp_list(t_envp_list **head, const char *key);
void		update_envp_list(t_envp_list **head, const char *k, const char *v);
void		get_key(t_envp_list *curr, const char *envp);
void		get_value(t_envp_list *curr, const char *envp);
char		**convert_envp_to_dptr(const t_envp_list *head);
void		sort_envp_dptr(char **envp);
t_envp_list	*find_list_by_key(t_envp_list *head, const char *key);
t_envp_list	*copy_envp_list(t_envp_list *head);
void		print_envp(t_envp_list *head, int op);

#endif