/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:28:49 by jaham             #+#    #+#             */
/*   Updated: 2022/02/15 20:30:54 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "terminal.h"
#include "libft.h"

void	free_both_cd(char **curr_dir, char **path)
{
	safe_free((void **) curr_dir);
	safe_free((void **) path);
}