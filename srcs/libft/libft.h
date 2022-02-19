/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:06:49 by jaham             #+#    #+#             */
/*   Updated: 2022/02/19 20:50:02 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

typedef struct s_buffer
{
	char			buf[BUFFER_SIZE];
	char			*cur;
	char			*end;
	int				fd;
	struct s_buffer	*next;
}	t_buffer;

typedef struct s_string
{
	char	*str;
	int		size;
	int		n;
}	t_string;

int		ft_isalpha(int c);
int		ft_isnum(int c);
int		ft_isnumstr(const char *str);
int		ft_atoi(const char *str);
ssize_t	ft_putstr_fd(const char *str, int fd);
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
char	*get_next_line(int fd);

#endif