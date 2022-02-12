/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:54:17 by jaham             #+#    #+#             */
/*   Updated: 2022/02/12 19:32:37 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "envp.h"

# define SHELL_NAME "minishell: "
# define EXPORT_ARG_ERR_MESSAGE "not a valid identifier\n"
# define EXPORT_CMD "export: "
# define UNSET_ARG_ERR_MESSAGE "not a valid identifier\n"
# define UNSET_CMD "unset: "

int	export(t_envp_list *envp, const char **argv);
int	unset(t_envp_list *envp, const char **argv);
int	env(t_envp_list *envp, const char **argv);
int	pwd(void);

#endif