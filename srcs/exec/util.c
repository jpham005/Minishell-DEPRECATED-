/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:58:08 by jaham             #+#    #+#             */
/*   Updated: 2022/02/26 12:27:51 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "temphead.h"

void	init_in_out(t_in_out *in_out)
{
	in_out->prev[0] = -1;
	in_out->prev[1] = -1;
	in_out->curr[0] = -1;
	in_out->curr[1] = -1;
}

void	set_in_out(t_in_out *in_out)
{
}
