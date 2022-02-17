// token, readline으로 입력받은 일련의 문자열을 의미 있게 쪼갠 단위

// lexer, lexer(lexical analysis(어휘 분석)), token을 만드는 함수명
// 보통 무난한 표현으로 tokenizer라고도 하는 듯

// parser, 앞선 단계를 통해 분석된 토큰을 묶어 구조적으로 나타냄, 그것을 parse tree라고 함
// 파서는 ~ 파이프 토큰까지의 단위

// command 함수가 해야 할 일이 가장 많음

// token은 무엇을 기준으로 쪼개야 직관적인가?
// bash docs를 보면서 이해하고 구현하기엔 너무 느릴 것이다... 애초에 전부 할 필요도 없고

// heredoc 처리 필요

#ifndef TEST_H
# define TEST_H

# include <unistd.h>
# include <stdio.h>
// # include <termios.h>
// # include <stdio.h>
// # include <signal.h>
// # include <readline/readline.h>
// # include <readline/history.h>
// #include <sys/types.h>
// #include <sys/wait.h>

# define ARG 101 // 내부에서 환경변수 expand, 와일드카드(*) 처리
# define COMMAND 102 // echo, cd, pwd, export, unset, env, exit
# define OPTION 103 // echo의 -m, cd 옵션 필요한가?(심볼릭링크), ...
# define PIPE 104 // |(control operator), &&(앞선 파서 동작시에만 뒤 파서 동작), ||
# define REDIR 105 // <, >, >>, (<<)
# define FILE 106 // a.txt, ...

// 귀찮아서 다른 헤더에서 가져온 부분
typedef struct s_envp_list
{
	char				*key;
	char				*value;
	size_t				list_len;
	struct s_envp_list	*next;
}	t_envp_list;

//

typedef struct  s_token
{
    char *str;
    int type;
    struct s_token *next;
}   t_token;

typedef struct  s_parse
{
    t_token *head;
    t_token *tail;

}   t_parse;

typedef struct s_command
{
    char *command;
    char *bin;

    int in;
    int out;
    int pipe[2];
    int type;

    t_token *arguments;
    t_envp_list *envp_list;
    
    struct s_command *next;
}   t_command;

# endif

// 시작과 파이프 직후에는 명령어가 나오고, command 뒤에는 arg가 나온다.
// token 매크로 덩어리들의 위치를 구하는 공식을 여러 개 정리한 후 함수로 구현해야 한다.