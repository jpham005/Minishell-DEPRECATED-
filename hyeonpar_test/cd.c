#include <unistd.h>
#include <stdio.h>

int main(void)
{
    char path[1024]; // 버퍼 사이즈 기준은 무엇인가?
    if (getcwd(path, 1024) == NULL)
        printf("get current working directory info failed\n");
    printf("%s\n", path);
    char *path2 = "/Users/hyeonpar/Minishell/hyeonpar_test/a"; // 상대경로이면 기존 path와 상대 경로 사이에 / 붙여서 join하면 됨, 절대이면 그냥 넣으면 됨
	// ~이면 환경변수에서 HOME key value 넣으면 되고 -면 출력도 해야됨
	// 인자 여러개일수 있지만 커맨드 바로 뒤 첫 인자만 보면 됨
    if (chdir(path2) != 0)
        printf("No such file or directory\n");
    printf("%s\n", getcwd(path, 1024));
}