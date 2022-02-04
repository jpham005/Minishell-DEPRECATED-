#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <termios.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// int	main() // exit status
// {
// 	int pid;
// 	int status;

// 	pid = fork();
// 	if (!pid)
// 	{
// 		sleep(2);
// 		printf("sleepdone\n");
// 		execvp("cat", NULL);
// 	}
// 	kill(pid, SIGTERM);
// 	waitpid(pid, &status, WUNTRACED);
// 	printf("status : %d\n", status);
// 	if (WIFEXITED(status))
// 		printf("exited\n");
// 	if (WIFSIGNALED(status))
// 		printf("signaled\n");
// 	printf("%d\n", WEXITSTATUS(status));
// 	printf("%d\n", WTERMSIG(status));
// }

/* list test
	del_one_envp_list(&sh_envp, "HOME");
	del_one_envp_list(&sh_envp, "exit_status");
	t_envp_list *asdf = sh_envp;
	for (; asdf; asdf = asdf->next)
		printf("%s=%s\n", asdf->key, asdf->value);
	printf("%zu\n", sh_envp->list_len);
*/

/* convert to dptr test
	char **ex = convert_to_dptr(sh_envp);
	for (int i = 0; ex[i]; i++)
		printf("%s\n", ex[i]);
*/

static int	asdf(void)
{
	return (0);
}

int	main(void)
{
	printf("%s\n", getenv("PATH"));
}
