/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:06:49 by jaham             #+#    #+#             */
/*   Updated: 2022/02/15 19:19:24 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>

int		ft_isalpha(int c);
int		ft_isnum(int c);
int		ft_isnumstr(const char *str);
int		ft_atoi(const char *str);
void	ft_putstr_fd(const char *str, int fd);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *str);
char	*ft_substr(const char *str, size_t start, size_t len);
void	ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(const char *str, char sep);
char	*ft_strchr(const char *str, int c);
char	*ft_getcwd(char *buf, size_t size);
void	free_c_dptr(char ***ptr);
void	*ft_malloc(size_t size, size_t n);
pid_t	ft_fork(void);
void	safe_free(void **ptr);
void	perror_exit(const char *str, unsigned int exit_status);

#endif