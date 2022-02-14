/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 21:51:24 by jaham             #+#    #+#             */
/*   Updated: 2022/02/14 15:32:05 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "envp.h"
#include "terminal.h"

int	env(t_context *context, const char **argv)
{
	if (!argv)
		return (1);
	print_envp(context->envp, UNSORT);
	return (0);
}
