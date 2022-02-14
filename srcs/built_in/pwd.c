/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:47:50 by jaham             #+#    #+#             */
/*   Updated: 2022/02/14 15:30:30 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "envp.h"

int	pwd(t_context *context, const char **argv)
{
	char	*dir;

	if (!context || !argv)
		return (1);
	dir = getcwd(NULL, 1);
	if (!dir)
	{
		perror("getcwd");
		exit(1);
	}
	printf("%s\n", dir);
	safe_free((void **) &dir);
	return (0);
}
