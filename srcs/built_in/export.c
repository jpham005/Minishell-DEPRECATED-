/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:44:39 by jaham             #+#    #+#             */
/*   Updated: 2022/02/05 21:51:42 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "envp.h"

static int	print_envp(t_envp_list *head)
{
	
}

int	export(const t_envp_list *head, const char *str)
{
	char	*key;
	char	*value;

	if (!str)
		print_envp(head);
	if (ft_strchr(str, '='))
		return (0);
	
}
// error : start with non_alpha && non _
//		ex) export 5=3 => `5=3': not a valid identifier
// error : = with space
//		ex) export asdf=4 asdf = a = = => export: `=': not a valid identifier * 3, successfully export asdf=4
// non_error : export (display declare -x ), export ex= (export ex with value blank), export name (do nothing)