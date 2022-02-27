/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par3_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonpar <hyeonpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:51:17 by jaham             #+#    #+#             */
/*   Updated: 2022/02/27 20:27:49 by hyeonpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

// char	*par3_helper(char **pars_str, int i, int ss_idx)
// {
// 	int		j;
// 	int		k;
// 	int		s_idx;
// 	char	*env_val;

// 	j = 0;
// 	while (pars_str[i][j] != '\0')
// 	{
// 		if (pars_str[i][j] == '$')
// 		{
// 			if (pars_str[i][j + 1] == '?')
// 				; // context->exit_status로 확장
// 			ss_idx = i;
// 			s_idx = j + 1;
// 			k = 1;
// 			while (pars_str[i][j + k] == '_' || ft_isdigit(pars_str[i][j + k]) || ft_isalpha(pars_str[i][j + k]))
// 				k++;
// 			env_val = ft_malloc(sizeof(char), k);
// 			ft_strlcpy(env_val, &pars_str[i][j + 1], k);
// 		}
// 		j++;
// 	}
// }
/* env 환경변수명 찾는 부분 " 포함해야 함 */
char **par3(char **pars_str, int flag_q, t_context *context)
{
	int i;
	int j;
	int k;
	char *env_val;
	int ss_idx;
	int s_idx;

	i = 0;
	env_val = NULL;
	ss_idx = 0;
	if (flag_q != 1)
	{
		while (pars_str[i] != NULL)
		{
			j = 0;
			while (pars_str[i][j] != '\0')
			{
				if (pars_str[i][j] == '$')
				{
					if (pars_str[i][j + 1] == '?')
						; // context->exit_status로 확장
					ss_idx = i;
					s_idx = j + 1;
					k = 1;
					while (pars_str[i][j + k] == '_' || ft_isdigit(pars_str[i][j + k]) || ft_isalpha(pars_str[i][j + k]))
						k++;
					env_val = ft_malloc(sizeof(char), k);
					ft_strlcpy(env_val, &pars_str[i][j + 1], k);
				}
				j++;
			}
			i++;
		}
	} // return (env_val);
	printf("env_val :: %s\n", env_val);

	/* env_list key:value */
	/* env_list cmp(env_val == list_key) : list_value ? loop */
	/*  */

	return (par4(pars_str, env_val, ss_idx, context));
}
