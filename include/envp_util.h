/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_util.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:48:23 by jaham             #+#    #+#             */
/*   Updated: 2022/02/03 20:36:33 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_UTIL_H
# define ENVP_UTIL_H

# include "manage_envp.h"

int		get_key(t_envp_list *curr, const char *envp);
int		get_value(t_envp_list *curr, const char *envp);
char	**convert_to_dptr(const t_envp_list *head);

#endif