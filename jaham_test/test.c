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
//		ex) export asdf=4 asdf = a = = 
	=> export: `=': not a valid identifier * 3, successfully export asdf=4
// error : start with =
// non_error : export (display declare -x ), 
	export ex= (export ex with value blank), export name (do nothing)
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

/* export && unset
	char **test = ft_split("asdf=3 zcxv=3 _DSaf=3 3415=4", ' ');
	export(sh_envp, NULL);
	t_envp_list *asdf = sh_envp;
	for (; asdf; asdf = asdf->next)
		printf("%s=%s\n", asdf->key, asdf->value);
	printf("---------------uset-------------------\n");
	char **test2 = ft_split("# adsf asdf zxcv _DSaf 3415", ' ');
	unset(sh_envp, (const char **) test2);
	t_envp_list *zcv = sh_envp;
	for (; zcv; zcv = zcv->next)
		printf("%s=%s\n", zcv->key, zcv->value);
*/

// unset : non error do nothing
// unset isenv isenv isenv : all del
// unset nonenv : return 0 do nothing
// unset non_alpha isenv : return 1, message, unset env
// unset # isenv : ignore after #
// unset # non_alpha : ignore after #, return 0

/*
exit => exit\n, term terminal with exit status
exit 4 => exit\n, term terminal with 4
exit 4 4 => bash: exit: too many arguments, doesnt exit, exit status 1
exit a => 
bash-3.2$ exit a
exit
bash: exit: a: numeric argument required
exit with 255
ignore after a, 
*/

/*
no arg => $HOME
additional arg => ignore
CDPATH => test path
success CDPATH, - => write(1, "path")
cd ../srcs
cd =>go to home
cd ..
cd ../
cd - : display oldpwd+\n, move to oldpwd
oldpwd
pwd
Not a directory
bash: cd: asdf: Permission denied
*/

/*
		//t_cmd_line	*cmd_line;

		//cmd_line = malloc(sizeof(t_cmd_line));
		//cmd_line->next = NULL;
		//cmd_line->type = PIPE;
		//cmd_line->pipes = malloc(sizeof(t_pipe));
		//cmd_line->pipes->cmds = malloc(sizeof(t_cmd) * 2);
		//cmd_line->pipes->len = 1;
		//cmd_line->pipes->cmds[0].redir = NULL;
		//cmd_line->pipes->cmds[0].type = PARENTHESIS;
		//cmd_line->pipes->cmds[1].type = SINGLE_CMD;
		//cmd_line->pipes->cmds[1].redir = &(t_redirect){
		//	REDIR_OUT,
		//	"fin",
		//	NULL
		//};
		//cmd_line->pipes->cmds[1].cmd = ft_split("cat", ' ');

		t_cmd_line	*cmd_line = malloc(sizeof(t_cmd_line));
		cmd_line->pipes = malloc(sizeof(t_pipe));
		cmd_line->pipes->type = PIPE;
		cmd_line->pipes->len = 3;
		cmd_line->pipes->cmds = malloc(sizeof(t_cmd) * 4);
		cmd_line->pipes->cmds[0].type = SINGLE_CMD;
		cmd_line->pipes->cmds[0].redir = NULL;
		// cmd_line->pipes->cmds[0].redir = malloc(sizeof(t_redirect));
		// cmd_line->pipes->cmds[0].redir->next = NULL;
		// cmd_line->pipes->cmds[0].redir->target = "infile";
		// cmd_line->pipes->cmds[0].redir->type = REDIR_HEREDOC;
		cmd_line->pipes->cmds[0].cmd = ft_split("cat", ' ');
		cmd_line->pipes->cmds[1].type = PARENTHESIS;
		cmd_line->pipes->cmds[1].redir = NULL;
		cmd_line->pipes->cmds[1].cmd = ft_split("ls", ' ');
		cmd_line->pipes->cmds[2].type = SINGLE_CMD;
		cmd_line->pipes->cmds[2].redir = NULL;
		cmd_line->pipes->cmds[2].cmd = ft_split("cat -e", ' ');

		cmd_line->next = NULL;

	/*
		cmd_line->next = malloc(sizeof(t_cmd_line));
		cmd_line->next->type = AND;
		cmd_line->next->pipes = malloc(sizeof(t_pipe));
		cmd_line->next->pipes->len = 3;
		cmd_line->next->pipes->cmds = malloc(sizeof(t_cmd) * cmd_line->next->pipes->len);
		
		cmd_line->next->pipes->cmds[0].type = SINGLE_CMD;
		cmd_line->next->pipes->cmds[0].cmd = ft_split("ls", ' ');
		cmd_line->next->pipes->cmds[0].redir = NULL;
		// cmd_line->next->pipes->cmds[0].redir = malloc(sizeof(t_redirect));
		// cmd_line->next->pipes->cmds[0].redir->type = REDIR_IN;
		// cmd_line->next->pipes->cmds[0].redir->target = "infile";
		// cmd_line->next->pipes->cmds[0].redir->next = NULL;

		cmd_line->next->pipes->cmds[1].type = SINGLE_CMD;
		cmd_line->next->pipes->cmds[1].cmd = ft_split("cat -e", ' ');
		// cmd_line->next->pipes->cmds[1].redir = NULL;
		cmd_line->next->pipes->cmds[1].redir = malloc(sizeof(t_redirect));
		cmd_line->next->pipes->cmds[1].redir->type = REDIR_OUT;
		cmd_line->next->pipes->cmds[1].redir->target = "outfile";
		cmd_line->next->pipes->cmds[1].redir->next = NULL;

		cmd_line->next->pipes->cmds[2].type = SINGLE_CMD;
		cmd_line->next->pipes->cmds[2].cmd = ft_split("cat -e", ' ');
		cmd_line->next->pipes->cmds[2].redir = NULL;
		// cmd_line->next->pipes->cmds[2].redir = malloc(sizeof(t_redirect));
		// cmd_line->next->pipes->cmds[2].redir->type = REDIR_IN;
		// cmd_line->next->pipes->cmds[2].redir->target = "infile";
		// cmd_line->next->pipes->cmds[2].redir->next = NULL;
		fprintf(stdout, "exit status %d\n", context->exit_status);
*/

int	main(void)
{
	printf("%s\n", getenv("PATH"));
}
