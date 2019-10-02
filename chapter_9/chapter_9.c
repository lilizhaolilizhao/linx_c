//
// Created by oneapm on 2019-10-02.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>

void my_signal_test();

void my_sigaction();

void wrong_return();

void right_return();

void my_kill();

/*信号处理函数*/
void handler_sigint(int signo) {
    printf("recv SIGINT\n");
}

int main(int argc, char *argv[], char **environ) {
//    my_signal_test();
//    my_sigaction();
//    wrong_return();
//    right_return();
    my_kill(argc, argv, environ);
}

void my_kill(int argc, char *argv[], char **environ) {
    int i, j;
    int signum = SIGTERM;    // 默认发送SIGTERM
    pid_t pid;

    /*首先检查参数个数*/;
    if (argc != 2 && argc != 4) {
        printf("Usage: ./my_kill <-s signum> [PID]\n");
        exit(0);
    }

    /*从命令行参数解析出信号编号*/
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-s")) {
            signum = atoi(argv[i + 1]);
            break;
        }
    }

    /*解析出进程号*/
    if (argc == 2) {
        pid = atoi(argv[1]);
    } else {
        for (j = 1; j < argc; j++) {
            if (j != i && j != i + 1) {
                pid = atoi(argv[j]);
                break;
            }
        }
    }

    if (kill(pid, signum) < 0) {
        perror("kill");
        exit(1);
    }
}

void right_return() {
//    /*设置返回点*/
//    switch (sigsetjmp(env, 1)) {	// sigsetjmp的第二个参数只要非0即可
//        case 0:
//            printf("return 0\n");
//            flag_saveenv = ENV_SAVED;
//            break;
//        case 1:
//            printf("return from SIGRTMIN+15\n");
//            break;
//        default:
//            printf("return else\n");
//            break;
//    }
//
//    /*捕捉信号，安装信号处理函数*/
//    signal(SIGRTMIN+15, handler_sigrtmin15);
//
//    while (1)
//        ;
}

jmp_buf env;     // 保存待跳转位置的栈信息

void wrong_return() {
//    /*设置返回点*/
//    switch (setjmp(env)) {
//        case 0:
//            break;
//        case 1:
//            printf("return from SIGRTMIN+15\n");
//            break;
//        case 2:
//            printf("return from SIGRTMAX-15\n");
//            break;
//        default:
//            break;
//    }
//
//    /*捕捉信号，安装信号处理函数*/
//    signal(SIGRTMIN+15, handler_sigrtmin15);
//    signal(SIGRTMAX-15, handler_sigrtmax15);
//
//    while (1)
//        ;
}

int temp = 0;

/*信号处理函数*/
void handler_sigint100(int signo) {
    printf("recv SIGINT\n");
    sleep(5);
    temp += 1;
    printf("the value of temp is: %d\n", temp);
    printf("in handler_sigint, after sleep\n");
}

void my_sigaction() {
    struct sigaction act;

    /*赋值act结构*/
    act.sa_handler = handler_sigint100;
    act.sa_flags = SIGTERM;
    /*安装信号处理函数*/
    sigaction(SIGINT, &act, NULL);

    while (1);
}

void my_signal_test() {
    /*安装信号处理函数*/
    signal(SIGINT, handler_sigint);

    while (1);
}

