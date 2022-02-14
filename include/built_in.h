/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:54:17 by jaham             #+#    #+#             */
/*   Updated: 2022/02/14 15:30:39 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "envp.h"
# include "terminal.h"

# define SHELL_NAME "minishell: "

# define EXPORT_CMD "export: "
# define UNSET_CMD "unset: "
# define EXPORT_ARG_ERR_MESSAGE "not a valid identifier\n"
# define UNSET_ARG_ERR_MESSAGE "not a valid identifier\n"

# define EXIT_CMD "exit: "
# define EXIT_NUMERIC 1 << 0
# define EXIT_NON_NUMERIC 1 << 1
# define EXIT_NON_NUMERIC_ERR_MESSAGE "numeric argument required\n"
# define EXIT_TOO_MANY_ARG 1 << 2
# define EXIT_TOO_MANY_ARG_ERR_MESSAGE "too many arguments\n"
# define EXIT_NO_ARG 1 << 3

int	built_in_exit(t_context *context, const char **argv);
int	export(t_context *context, const char **argv);
int	unset(t_context *context, const char **argv);
int	env(t_context *context, const char **argv);
int	pwd(t_context *context, const char **argv);

#endif