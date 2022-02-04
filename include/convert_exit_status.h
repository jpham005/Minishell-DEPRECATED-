/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:06:49 by jaham             #+#    #+#             */
/*   Updated: 2022/02/04 11:16:42 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_EXIT_STATUS_H
# define CONVERT_EXIT_STATUS_H

# include <unistd.h>
# include <stdlib.h>

char	*exit_status_to_a(int exit_status);

#endif