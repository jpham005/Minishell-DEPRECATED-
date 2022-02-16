/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:50:39 by jaham             #+#    #+#             */
/*   Updated: 2022/02/16 17:10:03 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "terminal.h"
#include "libft.h"

static char	*make_string(const char **argv)
{
	size_t	i;
	char	*ret;
	char	*temp;

	ret = ft_strdup("");
	while (argv[i])
	{
		temp = ft_strjoin(ret, argv[i]);
		free(ret);
		ret = temp;
		if (argv[i + 1])
		{
			temp = ft_strjoin(ret, " ");
			free(ret);
			ret = temp;
		}
		i++;
	}
	return (ret);
}

int	echo(t_context *context, const char **argv)
{
	char	*writing;
	int		ret;

	if (!context)
		return (1);
	if (!argv[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	writing = make_string(argv);
	if (write(1, writing, ft_strlen(writing)) == -1)
		ret = 1;
	else
		ret = 0;
	safe_free((void **) &writing);
	return (ret);
}
