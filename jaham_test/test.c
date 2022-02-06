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
	char **ex = convert_envp_to_dptr(sh_envp);
	for (int i = 0; ex[i]; i++)
		printf("%s\n", ex[i]);
*/

/* export
// error : start with non_alpha && non _
//		ex) export 5=3 => `5=3': not a valid identifier
// error : = with space
//		ex) export asdf=4 asdf = a = = => export: `=': not a valid identifier * 3, successfully export asdf=4
// error : start with =
// non_error : export (display declare -x ), export ex= (export ex with value blank), export name (do nothing)
// non_error : export # (display declare -x ) 

// export # a=1 -> ignore after # (include a=1 # b=1)
// export a=1 # -> ignore #

// when error occurred, no matter where is it, returns 1
*/

/* export test
	char **test = ft_split("a=", ' ');
	export(sh_envp, (const char **) test);
	free_c_dptr(&test);
	t_envp_list *asdf = sh_envp;
	for (; asdf; asdf = asdf->next)
		printf("%s=%s\n", asdf->key, asdf->value);
*/

int	main(void)
{
	printf("%s\n", getenv("PATH"));
}
