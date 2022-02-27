#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	*ft_malloc(size_t size, size_t n)
{
	void	*ret;

	ret = malloc(size * n);
	if (!ret)
	{
		perror("malloc");
		exit(1);
	}
	return (ret);
}
typedef enum e_redir_type
{
    REDIR_IN = 0, // >
    REDIR_HEREDOC, // <<
    REDIR_OUT, // <
    REDIR_APPEND // >>
}   t_redir_type;

typedef struct s_redirect
{
    t_redir_type type;
    char *target;
    struct s_redirect *next;
}   t_redirect;

t_redirect	*init_redirect(t_redir_type type, char *target)
{
	t_redirect *red;

	red = ft_malloc(sizeof(t_redirect), 1);
	red->type = type;
	red->target = target;
	red->next = NULL;

	return (red);
}

void	add_redirect(t_redirect *red, t_redir_type type, char *target)
{
	t_redirect *new;

	new = init_redirect(type, target);
	red->next = new;
}

// 구조체 free 함수 만들어야 함

int	main(void)
{
	t_redirect *a;

	a = init_redirect(REDIR_IN, "a");
	add_redirect(a, REDIR_OUT, "b");
	printf("%d\n", a->type);
	printf("%s\n", a->target);
	printf("%d\n", a->next->type);
	printf("%s\n", a->next->target);
}