#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

extern char	**ft_split(char const *s, char c);
extern size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);

typedef struct s_env
{
    char **env_path;
}   t_env;

char *ft_strjoin(char *s1, char *s2)
{
    char *str = (char *)malloc(strlen(s1) + strlen(s2) + 1);
    int i = 0;

    while (*s1 != NULL)
    {
        str[i++] = *s1++;
    }
    while (*s2 != NULL)
    {
        str[i++] = *s2++;
    }
    str[i] = '\0';
    return (str);
}

int ft_strcmp(char *s1, char *s2)
{
    if (s1 == NULL || s2 == NULL)
        return (1);
    return (strcmp(s1, s2));
}

int ft_strlen(char *s)
{
    if (s == NULL)
        return (0);
    return (strlen(s));
}

void    del_q(char *str, char c)
{
    int i = 0;
    while (str[i] != '\0')
    {
        str[i] = str[i + 1];
        i++;
    }
}

char    **find_path(char *str, char **envp)
{
    // char *p = "PATH=";
    char **path;
    int i;
    
    /* path_list */
    i = 0;
    while (*(envp + i) != NULL)
    {
        // printf("%s\n", *(envp + i));
        if (envp[i][0] == 'P' && envp[i][1] == 'A' &&
        envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
        {
            path = ft_split(&envp[i][5], ':');
            break;
        }
        i++;
    }

    /* split str (readline) */
    char **cmd_str = ft_split(str, ' ');

    // [/usr/bin + / + cmd]
    i = 0;
    char *tmp;
    char *cmd_path;
    while (*(path + i) != NULL)
    {
        tmp = ft_strjoin(path[i], "/");
        cmd_path = ft_strjoin(tmp, cmd_str[0]);
        if (access(cmd_path, X_OK) == 0)
            break;
        i++;
    }
    free(tmp);
    tmp = cmd_str[0];
    cmd_str[0] = cmd_path;
    free(tmp);
    return (cmd_str); // /ooo/ooo/cmd
}

char **par(char *str, char **envp)
{
    // check str, check_readline(); == false
    char **pars_str = find_path(str, envp);
    int i = 0;

    while (*(pars_str + i) != NULL)
    {
        printf("%s\n", *(pars_str + i));
        i++;
    }

    printf("==========================\n");
    // char *echo[] = {"/bin/ls", "err", "*", NULL};
	// char **cmd[] = {echo, NULL};
    // execve("/bin/ls", cmd[0], envp);
    // execve(pars_str[0], pars_str, envp);

    /* del q */
    i = 0;
    int flag_q = 0;
    int flag_qq = 0;

    while (*(pars_str + i) != NULL)
    {
        if (pars_str[i][0] == '\'')
        {
            del_q(pars_str[i], '\''); // 'err\0 --> err\0\0     ||      err'\0 --> err\0\0
            flag_q = 1;
        }
        else if (pars_str[i][0] == '\"')
        {
            del_q(pars_str[i], '\"');
            flag_qq = 1;
        }
        if (pars_str[i + 1] == NULL && (flag_q || flag_qq))
        {
            int j = 0;
            while (pars_str[i][j] != '\0')
            {
                if (pars_str[i][j + 1] == '\0')
                    pars_str[i][j] = '\0';
                j++;
            }
        }
        i++;
    }

    /* env 환경변수명 찾는 부분 " 포함해야 함 */
    i = 0;
    char *env_val = NULL;
    int ss_idx = 0;
    if (flag_q != 1)
    {
        while (pars_str[i] != NULL)
        {
            int j = 0;
            while (pars_str[i][j] != '\0')
            {
                if (pars_str[i][j] == '$')
                {
                    ss_idx = i;
                    int s_idx = j + 1;
                    int k = 1;
                    while (pars_str[i][j + k] == '_' || isdigit(pars_str[i][j + k]) || isalpha(pars_str[i][j + k]))
                    {
                        k++;
                    }
                    env_val = (char *)malloc(k);
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
    char *list_key = "SHELL";
    char *value = NULL;
    if (ft_strcmp(list_key, env_val) == 0)
        value = strdup("/bin/bash"); // strdup() == list_value
    char *ex_str = NULL;

    // "$SHELL-123" --> /bin/bash-123
    int len = ft_strlen(pars_str[ss_idx]) - ft_strlen(env_val) + 1 + ft_strlen(value);
    ex_str = (char *)malloc(len + 1);
    i = -1;
    int j = 0;
    if (ss_idx != 0)
    {
        while (pars_str[ss_idx][++i] != '$')
            ex_str[i] = pars_str[ss_idx][i];
        if (value != NULL)
        {
            int idx = i + strlen(env_val);
            while (value[j] != '\0')
                ex_str[i++] = value[j++];
            while (pars_str[ss_idx][++idx] != '\0')
                ex_str[i++] = pars_str[ss_idx][idx];
            printf("ex-str :: %s\n", ex_str);
        }
        ex_str[i] = '\0';
        free(pars_str[ss_idx]);
        pars_str[ss_idx] = ex_str;
    }

    i = 0;
    while (*(pars_str + i) != NULL)
    {
        printf("%s\n", *(pars_str + i));
        i++;
    }
    return (pars_str);
}

void    ft_exec(char **rtc)
{
    // fork()
    printf("\n================\n");
    execve(rtc[0], rtc, NULL); // 프로세스 CMD로 넘어가므로 일반적으로 하단은 실행 안 됨
    printf("\n================\n"); // 하단
}

int main(int argc, char *argv[], char *envp[])
{
    // char *str = strdup("echo -n $SHELL"); // << readline 입력한 문자열
    char *str = strdup("echo $SHELL"); // << readline 입력한 문자열

    // check str, check_readline(); == false
    char **readline_to_cmd = par(str, envp);
    ft_exec(readline_to_cmd);
    
    free(str);
    return (0);
}