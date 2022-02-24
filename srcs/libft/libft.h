/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaham <jaham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:06:49 by jaham             #+#    #+#             */
/*   Updated: 2022/02/24 18:27:20 by jaham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>

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
void	ft_waitpid(pid_t pid, int *status, int op);
int		ft_wifexited(int status);
int		ft_wexitstatus(int status);
int		ft_wifsignaled(int status);
int		ft_wtermsig(int status);
void	exit_by_errno(int errno, char *cmd);
int		ft_pipe(int pipefd[2]);
int		ft_dup2(int fd1, int fd2);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_strdup_err(char *s1, char *s2);
void	ft_close(int fd);

#endif